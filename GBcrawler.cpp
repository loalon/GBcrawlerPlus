
// GBcrawler.cpp
#include "GBcrawler.h"

#define SECTION_HEAD 0
#define SECTION_KEYWORDS 1
#define SECTION_SOURCE 2
#define SECTION_REFERENCE 3
#define SECTION_COMMENT 4
#define SECTION_FEATURES 5
#define SECTION_OBSOLETE 6
#define SECTION_ORIGIN 7
#define SECTION_NULL 8


GBfeature::GBfeature() {
	this->begin=0;
	this->end=0;
	this->type="";
}

GBfeature::GBfeature(int begin, int end, std::string type) {
	
	this->begin=begin;
	this->end=end;
	this->type=type;
	/*
	bool complementary=false;
	bool beginIsBeyond=false;
	bool endIsBeyond=false;
	bool betweenBases=false;
	//qualifierDict={}
	bool pseudo=false;
	*/
	
}

GBcrawler::GBcrawler(std::string fn) {
	
	bool windowsFormat=false;
	std::unordered_set<std::string> divisionTypes={"PRI","ROD","MAM","VRT","INV"
	,"PLN","BCT","VRL","PHG","SYN","UNA","EST","PAT","STS","GSS","HTG","HTC",
	"ENV","CON","TSA","   "};
  filename=fn;

	size_t mode = SECTION_HEAD;
  std::string line;
  std::ifstream in(fn);
	
	std::string tempReference;
	GBfeature tempFeature;
	std::string tempQualifierKey;
	std::string tempQualifierValue;
		
		
  /*1st line*/
  std::getline(in, line);
  std::cout<<line<<'\n';

	if (line[line.length()-1]=='\r') {
		std::cout<<"Windows format"<<std::endl;
		line=line.substr(0, line.length()-1);
		windowsFormat=true;
	}
  sequenceID = line.substr (12,16); 
	sequenceLength = std::stoi(line.substr (29,11)); 
	strand = line.substr (44,3); 
	moleculeType = line.substr (47,6); 
	division = line.substr (64,3); 
	if(divisionTypes.find(division) == divisionTypes.end()) {
		std::cout<<"Division Type doesn't match"<<std::endl;
		exit(-1);
	}
	modDate = line.substr (68,11); 
 
	/* OTHER LINES */
	
  while (std::getline(in, line)) {
			if (line[line.length()-1]=='\r') {
		
		line=line.substr(0, line.length()-1);
	}
		if (line.compare(0, 1, " ") == 0){ //skip if not a field
			//do nothing;
		} else if (line.compare(0, 8, "KEYWORDS") == 0){
			mode = SECTION_KEYWORDS;
		} else if (line.compare(0, 6, "SOURCE") == 0){
			mode = SECTION_SOURCE;
			source = line.substr(12,std::string::npos);
		} else if (line.compare(0, 9, "REFERENCE") == 0){
			mode = SECTION_REFERENCE;
			if (!tempReference.empty()){
				referenceList.push_back(tempReference);
				tempReference="";
			}

		} else if (line.compare(0, 7, "COMMENT") == 0){
			if (!tempReference.empty()){
				referenceList.push_back(tempReference);
				tempReference="";
			}
			mode = SECTION_COMMENT;
			//continue;
		} else if (line.compare(0, 8, "FEATURES") == 0){
				//#need to append last feature
				//self.featureList.append(tempFeature)
			mode = SECTION_FEATURES;
			continue;
		} else if (line.compare(0, 6, "ORIGIN") == 0) {
      //firstLine=line;
			mode = SECTION_ORIGIN;
			continue;
		} else if (line.compare(0, 10, "BASE COUNT") == 0){
			mode = SECTION_OBSOLETE;
			continue;
			
		} 

		
		
		
		if (mode==SECTION_ORIGIN) {
			for(char& c : line) {
				if (isalpha(c)) {
					sequence.push_back(c);
				}	
			}
		} else if (mode==SECTION_HEAD) {
				if (line.compare(0, 10, "DEFINITION") == 0){
					definition=line.substr(12,std::string::npos);
					std::cout<<definition<<std::endl;
				} else if (line.compare(0, 9, "ACCESSION") == 0){
					accession=line.substr(12,std::string::npos);
				} else if (line.compare(0, 7, "VERSION") == 0){
					version=line.substr(12,std::string::npos);
				}
		} else if (mode==SECTION_KEYWORDS) { // KEYWORDS
			//if(windowsFormat)
				//line=line.substr(0, line.length()-1);
			std::string tempString="";
			for(char& c : line.substr(12, std::string::npos)) {
				
				if (c!=',' && c!='.') {
					tempString+=c;
					//std::cout<<tempString<<"\n";
				} else if(c==',') {
					keywords.push_back(tempString);
					tempString="";
					
				} else if (c=='.') {
					if (!tempString.empty())
						keywords.push_back(tempString);
					continue;
				}
			
			}
			if (!tempString.empty()) //push the last one
				keywords.push_back(tempString);
		}	else if (mode==SECTION_REFERENCE) { //REFERENCE
			tempReference+=line.substr(12,std::string::npos);
			tempReference+='\n';

		}	else if (mode==SECTION_COMMENT) { //COMMENT
			comment.append(line.substr(12,std::string::npos));
			comment.append("\n");
		} else if (mode==SECTION_SOURCE) {
			//source = line.substr(12,std::string::npos);
		} 
		else { continue;}

		
  } //end for each line
	
}

std::string GBcrawler::getFilename() {
  return firstLine;
}

std::string GBcrawler::getID() {
  return sequenceID;
}

int GBcrawler::getLength() {
  return sequenceLength;
}

std::string GBcrawler::getStrand() {
  return strand;
}

std::string GBcrawler::getType() {
  return moleculeType;
}

std::string GBcrawler::getDivision() {
  return division;
}

std::string GBcrawler::getDate() {
  return modDate;
}

std::string GBcrawler::getDefinition() {
  return definition;
}

std::string GBcrawler::getAccession() {
  return accession;
}

std::string GBcrawler::getVersion() {
  return version;
}

std::vector<std::string> GBcrawler::getKeywords(){
	return keywords;
}
std::string GBcrawler::getOrganism() {
  return source;
}
std::string GBcrawler::getComment() {
  return comment;
}

std::vector<char> GBcrawler::getSequence() {
  return sequence;
}

std::vector<std::string> GBcrawler::getReferences(){
	return referenceList;
}


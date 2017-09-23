// GBcrawler.h
#ifndef GBcrawler_H
#define GBcrawler_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stdio.h>
#include <ctype.h>

class GBfeature {
	private:
		int begin;
		int end;
		std::string type;
		bool complementary=false;
		bool beginIsBeyond=false;
		bool endIsBeyond=false;
		bool betweenBases=false;
		//qualifierDict={}
		bool pseudo=false;
		
		public:
			GBfeature();
			GBfeature(int,int,std::string);
};


class GBcrawler {
	private:
		int length;
		std::string filename;
		
		
		std::string sequenceID;
		int sequenceLength;
		std::string strand;
		std::string moleculeType;
		std::string division;
		std::string modDate;
		std::string definition;
		std::string accession;
		std::string version;
		std::vector<std::string> keywords;
		std::string source;
		std::string comment;
		
		std::vector<std::string> referenceList;
		//std::vector<GBfeature> featureList;
		std::vector<char> sequence;
		
		
		std::string firstLine;

	public:
		GBcrawler(std::string);
		std::string getFilename();
		int getLength();
		std::string getID();
		std::string getStrand();
		std::string getType();
		std::string getDivision();
		std::string getDate();
		std::string getDefinition();
		std::string getAccession();
		std::string getVersion();
		std::vector<std::string> getKeywords();
		std::string getOrganism(); 
		std::string getComment(); 
		std::vector<char> getSequence();
		std::vector<std::string> getReferences();
	
		

};

#endif
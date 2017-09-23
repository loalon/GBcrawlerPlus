#include "GBcrawler.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[] ) {
	GBcrawler geneinfo(argv[1]);
	std::cout<<geneinfo.getFilename()<<std::endl;
	std::cout<<"ID: "<<geneinfo.getID()<<std::endl;
	std::cout<<"length: "<<geneinfo.getLength()<<std::endl;
	std::cout<<"length: "<<geneinfo.getType()<<std::endl;
	std::cout<<"length: "<<geneinfo.getDivision()<<std::endl;
	std::cout<<"length: "<<geneinfo.getDate()<<std::endl;
		std::cout<<"def: "<<geneinfo.getDefinition()<<std::endl;
	std::cout<<"accession: "<<geneinfo.getAccession()<<std::endl;
		std::cout<<"version: "<<geneinfo.getVersion()<<std::endl;
	std::cout<<"length: "<<geneinfo.getSequence().size()<<std::endl;
	//std::cout<<"comment: "<<geneinfo.getComment()<<std::endl;

		
	//for (std::vector<std::string>::const_iterator i = geneinfo.getKeywords().begin(); i != 
	//geneinfo.getKeywords().end(); ++i)
	for (auto i:geneinfo.getKeywords())
    std::cout << i << ' ';
	std::cout<<"source: "<<geneinfo.getOrganism()<<std::endl;
	
		for (auto i:geneinfo.getReferences())
			std::cout << i << ' ';
	std::cout<<"reference length: "<<geneinfo.getReferences().size()<<std::endl;
	/*
	std::cout<<"length: "<<geneinfo.getAccesion()<<std::endl;
	std::cout<<"length: "<<geneinfo.getVersion()<<std::endl;
	std::cout<<"length: "<<geneinfo.getComment()<<std::endl;*/
	//std::cout<<"sequence: "<<geneinfo.getSequence()<<std::endl;
	/*
	for (std::vector<char>::const_iterator i = geneinfo.getSequence().begin(); i != 
	geneinfo.getSequence().end(); ++i)
    std::cout << *i << ' ';
	*/

	return 0;
}
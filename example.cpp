#include <GBcrawler.h>



int main(int argc, char* argv[] ) {
	GBcrawler geneinfo (argv[1]);
	std::cout<<geneinfo.getLength()<<std::endl;
	return 0;
}
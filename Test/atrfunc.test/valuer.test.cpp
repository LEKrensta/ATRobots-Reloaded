#include <string>
#include <iostream>
#include "../maccHeaders/Macchiato.h"
#include "../../bin/atrrfunc.hh"
using namespace Macchiato;

void valuer_test();

void valuer_test(){
    	describe("Testing valuer(char *i)", [&]() {
			it("i = '10.5'", [&]() {
			    return expect(valuer("10.5")).to->equal(10.5)->getResult();
			});
	    });

     
}  	
   


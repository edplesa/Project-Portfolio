//  Author: Edward Plesa, Project 3, Spring 2021

#include <iostream>
#include "barchartanimate.h"
using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarOperators()
{
	Bar b1("Chicago", 1000, "US");
	Bar b2("India", 900, "US");
	Bar b3("China", 2000, "US");
	Bar b4("Arabia", 1000, "US");
	
	if ( (b1 > b2) != true) {
		cout << "testBarOperator: > failed" << endl;
	}
	else if ( (b1 <= b4) != true) {
		cout << "testBarOperator: <= failed" << endl;
	}
	else if ( (b1 >= b4) != true) {
		cout << "testBarOperator: >= failed" << endl;
	}
	else if ( (b1 < b3) != true) {
		cout << "testBarOperator: < failed" << endl;
	}
	else if ( (b1 < b2) != false) {
		cout << "testBarOperator: > failed" << endl;
	}
	else if ( (b1 > b3) != false) {
		cout << "testBarOperator: < failed" << endl;
	}
	cout << "testBarOperators: all passed!" << endl;
    return true;
}

bool testBarChartDefaultConstructor() {
	BarChart b;
    if (b.getFrame() != "") {
    	cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
    	return false;
    } 
    else if (b.getSize() != 0) {
    	cout << "testBarChartDefaultConstructor: getSize failed" << endl;
    	return false;
    }
    cout << "testBarChartDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarChartParamConstructor() {
	BarChart b(10);
	BarChart bCopy(b);
	BarChart bCopyTest(10);
	bCopyTest.setFrame("999");
	BarChart copyOp;
	copyOp = bCopyTest;
    if (b.getFrame() != "") {
    	cout << "testBarChartParamConstructor: getFrame failed" << endl;
    	return false;
    } 
    else if (b.getSize() != 0) {
    	cout << "testBarChartParamConstructor: getSize failed" << endl;
    	return false;
    }
    else if (bCopy.getSize() != 0) {
    	cout << "testBarChartParamConstructor: getSize failed" << endl;
    	return false;
    }
    else if (bCopy.getFrame() != "") {
    	cout << "testBarChartParamConstructor: getFrame failed" << endl;
    	return false;
    }
    else if (copyOp.getFrame() != "999") {
    	cout << "testBarChartParamConstructor: getFrame failed" << endl;
    	return false;
    }
    else if (copyOp.getSize() != 0) {
    	cout << "testBarChartParamConstructor: getSize failed" << endl;
    	return false;
    }
    cout << "testBarChartParamConstructor: all passed!" << endl;
    return true;
}

bool testBarChartSetGetClearandAdd() {
	BarChart b(1);
	b.setFrame("100");
	b.addBar("Chicago", 1020, "US");
	if (b.getFrame() != "100") {
		cout << "testBarChartSetAndGetAndClear: getFrame failed" << endl;
		return false;
	}
	else if (b.getSize() != 1) {
		cout << "testBarChartSetAndGetAndClear: addBar: size failed" << endl;
		return false;
	}
	b.clear();
	if (b.getFrame() != "") {
		cout << "testBarChartSetAndGetAndClear: clear: frame failed" << endl;
		return false;
	}
	else if (b.getSize() != 0) {
		cout << "testBarChartSetAndGetAndClear: clear: size failed" << endl;
		return false;
	}
	cout << "testBarChartSetAndGetAndClear: all passed!" << endl;
    return true;
}

void testBarChartSquareOperatorAndDumpAndGraph() {
	BarChart bc(3);
	bc.setFrame("1950");
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	int n = bc.getSize();
	for (int i = 0; i < n; i++) {
	  cout << bc[i].getName() << " ";
	  cout << bc[i].getValue() << " ";
	  cout << bc[i].getCategory();
	  cout << endl;
	}
	cout << endl << "After dump:" << endl;
	bc.dump(cout);
	map<string, string> colorMap;
	bc.graph(cout, colorMap, 3);
	string red("\033[1;36m");
	string blue("\033[1;33m");
	colorMap["US"] = red;
	colorMap["France"] = blue;
	bc.graph(cout, colorMap, 3);
}

bool testBarChartAnimateParamConstructor() {
	string title = "this is title";
	string xlabel = "this is label";
	string source = "this is source";
	BarChartAnimate bca(title, xlabel, source);
	if (bca.getTitle() !=  "this is title") {
		cout << "testBarChartAnimateParamConstructor:getTitle() failed" << endl;
		return false;
	}
	else  if (bca.getSource() != "this is source") {
		cout << "testBarChartAnimateParamConstructor:getSource() failed" << endl;
		return  false;
	}
	else if (bca.getLabel() != "this is label") {
		cout << "testBarChartAnimateParamConstructor:getLabel() failed" << endl;
		return false;
	}
	else if (bca.getSize() != 0) {
		cout << "testBarChartAnimateParamConstructor:getSize() failed" << endl;
		return false;
	}
	cout << "testBarChartAnimateParamConstructor: all passed!" << endl;
	return true;
}



int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
	testBarOperators();
	testBarChartDefaultConstructor();
	testBarChartParamConstructor();
	testBarChartSetGetClearandAdd();
	testBarChartSquareOperatorAndDumpAndGraph();
	testBarChartAnimateParamConstructor();
    return 0;
}
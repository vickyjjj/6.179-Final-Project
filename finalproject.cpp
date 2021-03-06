#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <cmath>
#include <unistd.h>
#include "gnuplot_i.hpp"

// 6.179 Final Project January 2018
// Colin Chaney and Victoria Juan

class ListHandler{
	std::vector<double> list1;
  std::vector<double> sortedList1;
	double total1 = 0;
	double mean1 = 0;
	double standardErrorSum1 = 0;
	double standardDeviation1 = 0;
	double variance1 = 0;
	double max1 = 0;
	double min1 = 0;
	double median1 = 0;

	std::vector<double> list2;
  std::vector<double> sortedList2;
  std::vector<double> residual;
	double total2 = 0;
	double mean2 = 0;
	double standardErrorSum2 = 0;
	double standardDeviation2 = 0;
	double variance2 = 0;
	double max2 = 0;
	double min2 = 0;
	double median2 = 0;

	public:
    ListHandler(){

		}

		void addToList(int listNum);
    void removeFromList(int listNum);
    void removeAll(int listNum);
		void plot();
		void plotWithLine(int num, std::vector<double> nums);

    friend std::ostream &operator<<(std::ostream &os, ListHandler &lh);

    std::vector<double> allNums1() const;
    std::vector<double> allNums2() const;

    // Colin's functions, written in the class definition itself

    std::vector<double> createLinearRegression(){
			std::vector<double> values;
      if(list1.size() != list2.size()){
        std::cout << "Lists are not the same length and a linear regression can't be done" << std::endl;
      }
      else{
        statsOf1(false);
        statsOf2(false);
        double sumOfXTimesY = 0;
        double sumOfXSquared = 0;
        for(int i = 0; i < list1.size(); i++){
          sumOfXTimesY += (list1[i] * list2[i]);
          sumOfXSquared += pow(list1[i], 2);
        }
        double a = (total2 * sumOfXSquared - total1 * sumOfXTimesY) / ( list1.size() * sumOfXSquared - pow(total1, 2));
        double b = ( list1.size() * sumOfXTimesY - total1 * total2 ) / ( list1.size() * sumOfXSquared - pow(total1, 2) );
        double SSR = 0;
        double SSTO = 0;
        double expectedValue = 0;
        for(int i = 0; i < list1.size(); i++){
          expectedValue = list1[i] * b + a;
          residual.push_back(list2[i] - expectedValue);
          SSR += pow( expectedValue - mean2, 2);
          SSTO += pow( list2[i] - mean2, 2);
        }
        double rSquared = SSR/SSTO;
        std::cout << "Offset: " << a << "   Slope: " << b << "   Y = " << b << "*x + " << a << "   R Squared: " << rSquared << std::endl;
				values.push_back(a);
				values.push_back(b);
				return values;
      }
    }

		void assignList1(std::vector<double> list){
			list1 = list;
		}

		void assignList2(std::vector<double> list){
			list2 = list;
		}

		void statsOf1(bool printOut){
      if(list1.empty()){
        std::cout << "error: list isn't filled" << std::endl;
      }
      else{

        total1 = 0;
        sortList1();
        for(auto number: list1){
          total1 += number;
        }
        mean1 = total1 / list1.size();

        standardErrorSum1 = 0;
        for(auto number: list1){
          standardErrorSum1 += pow(number-mean1, 2);
        }

        standardDeviation1 = pow(standardErrorSum1 / (list1.size() - 1), 0.5);
        variance1 = pow(standardDeviation1, 2);

        max1 = sortedList1[sortedList1.size() - 1];
        min1 = sortedList1[0];

        if(sortedList1.size() % 2 == 0){
          median1 = (sortedList1[(sortedList1.size()-1)/2 + 1] + sortedList1[(sortedList1.size() - 1) / 2])/2;
        }
        else{
          median1 = sortedList1[(sortedList1.size() - 1 )/ 2];
        }
        if(printOut){
          std::cout << "Mean: " << mean1 << "    Standard Error: " << standardErrorSum1 << "    Standard Deviation: " << standardDeviation1 << std::endl << "Variance: " << variance1 <<  "    Min: " << min1 << "    Median: " << median1 << "    Max: " << max1 <<  std::endl;
        }
      }
    }

		void statsOf2(bool printOut){
      if(list2.empty()){
        std::cout << "error: list isn't filled" << std::endl;
      }
      else{

        total2 = 0;
        sortList2();
        for(auto number: list2){
          total2 += number;
      }
      mean2 = total2 / list2.size();

      standardErrorSum2 = 0;
      for(auto number: list2){
        standardErrorSum2 += pow(number-mean2, 2);
      }

      standardDeviation2 = pow(standardErrorSum2 / (list2.size() - 1), 0.5);
      variance2 = pow(standardDeviation2, 2);

      max2 = sortedList2[sortedList2.size() - 1];
      min2 = sortedList2[0];

      if(sortedList2.size() % 2 == 0){
        median2 = (sortedList2[(sortedList2.size()-1)/2 + 1] + sortedList2[(sortedList2.size() - 1) / 2])/2;
      }
      else{
        median2 = sortedList2[(sortedList2.size() - 1 )/ 2];
      }
      if(printOut){
        std::cout << "Mean: " << mean2 << "    Standard Error: " << standardErrorSum2 << "    Standard Deviation: " << standardDeviation2 << std::endl << "Variance: " << variance2 <<  "    Min: " << min2 << "    Median: " << median2 << "    Max: " << max2 <<  std::endl;
      }
    }
  }

	void isLikely1(double number){
		statsOf1(false);
		if((number-mean1)/standardDeviation1 > 1.64485 || (number-mean1)/standardDeviation1 < -1.64485){
			std::cout << "It is not likely that this number is part of this list" << std::endl;
		}
		else{
			std::cout << "It is likely that this number is part of this list" << std::endl;
		}
	}

	void isLikely2(double number){
		statsOf2(false);
		if((number-mean2)/standardDeviation2 > 1.64485 || (number-mean2)/standardDeviation2 < -1.64485){
			std::cout << "It is not likely that this number is part of this list" << std::endl;
		}
		else{
			std::cout << "It is likely that this number is part of thsi list" << std::endl;
		}
	}

	void sortList1(){
  sortedList1 = list1;
    int n = sortedList1.size();
    int min = 0;
    double tempNumber = 0;
    for(int j = 0; j < n-1; j++){
      min = j;
      for(int i = j+1; i < n; i++){
        if(sortedList1[i] < sortedList1[min]){
          min = i;
        }
      }
      if(min != j){
        tempNumber = sortedList1[j];
        sortedList1[j] = sortedList1[min];
        sortedList1[min] = tempNumber;
      }
    }
  }

	void sortList2(){
  sortedList2 = list2;
    int n = sortedList2.size();
    int min = 0;
    double tempNumber = 0;
    for(int j = 0; j < n-1; j++){
      min = j;
      for(int i = j+1; i < n; i++){
        if(sortedList2[i] < sortedList2[min]){
          min = i;
        }
      }
      if(min != j){
        tempNumber = sortedList2[j];
        sortedList2[j] = sortedList2[min];
        sortedList2[min] = tempNumber;
      }
    }
  }

  void compare(){
    statsOf1(false);
    statsOf2(false);
    int degressOfFreedom = pow( variance1/list1.size() + variance2/list2.size() ,2) / (  pow(variance1/list1.size(),2)/(list1.size() - 1)  + pow(variance2/list2.size(),2)/(list2.size() - 1)           );
    double requiredT = 0;
    switch(degressOfFreedom){
      case 1: requiredT = 6.313752; break;
      case 2: requiredT = 2.919986; break;
      case 3: requiredT = 2.353363; break;
      case 4: requiredT = 2.131847; break;
      case 5: requiredT = 2.015048; break;
      case 6: requiredT = 1.943180; break;
      case 7: requiredT = 1.894579; break;
      case 8: requiredT = 1.859548; break;
      case 9: requiredT = 1.833113; break;
      case 10: requiredT = 1.812461; break;
      case 11: requiredT = 1.795885; break;
      case 12: requiredT = 1.782288; break;
      case 13: requiredT = 1.770933; break;
      case 14: requiredT = 1.761310; break;
      case 15: requiredT = 1.753050; break;
      case 16: requiredT = 1.745884; break;
      case 17: requiredT = 1.739607; break;
      case 18: requiredT = 1.734064; break;
      case 19: requiredT = 1.729133; break;
      case 20: requiredT = 1.724718; break;
      case 21: requiredT = 1.720743; break;
      case 22: requiredT = 1.717144; break;
      case 23: requiredT = 1.713872; break;
      case 24: requiredT = 1.710882; break;
      case 25: requiredT = 1.708141; break;
      case 26: requiredT = 1.705618; break;
      case 27: requiredT = 1.703288; break;
      case 28: requiredT = 1.701131; break;
      case 29: requiredT = 1.699127; break;
      case 30: requiredT = 1.697261; break;
      default: requiredT = 1.644854; break;
    }
    double pooledStandardDeviation = pow( ((list1.size() - 1)*pow(standardDeviation1, 2) + (list2.size() - 1)*pow(standardDeviation2, 2)) / ( list1.size() + list2.size() -2 ), 0.5 );
    double actualT = (mean1-mean2) / ( pooledStandardDeviation * pow( 1.0/list1.size() + 1.0/list2.size(), 0.5 ) );
    if(actualT > requiredT || actualT < -requiredT){
      if(actualT > requiredT){
        std::cout << "With 95% confidence, we can say that the population list1 has a higher mean than population of list2" << std::endl;
      }
      else{
        std::cout << "With 95% confidence, we can say that the population list2 has a higher mean than population of list1" << std::endl;
      }
    }
    else{
      std::cout << "With 95% confidence, we can say the population means of list1 and list2 are similar" << std::endl;
    }
  }
};

// class functions

std::vector<double> ListHandler::allNums1() const
{
  std::vector<double> allNums;
  for (double const &x : this->list1) {
    allNums.push_back(x);
  }
  return allNums;
}

std::vector<double> ListHandler::allNums2() const
{
  std::vector<double> allNums;
  for (double const &x : this->list2) {
    allNums.push_back(x);
  }
  return allNums;
}

void ListHandler::plot() {
	std::vector<double> x = this->list1;
  std::vector<double> y = this->list2;

	try {
		Gnuplot g1 = Gnuplot("Plot");
		g1.set_style("points");
		g1.plot_xy(x,y,"Point");
		sleep(15);
	} catch (GnuplotException ge) {
		std::cout << ge.what() << std::endl;
	}
}

void ListHandler::plotWithLine(int num, std::vector<double> nums) {

	std::vector<double> x;
  std::vector<double> y;

	if (num == 0) {
		x = this->list1;
		y = this->residual;
	} else {
		x = this->list1;
		y = this->list2;
	}

	double a = nums[0];
	double b = nums[1];

	try {
		Gnuplot g1 = Gnuplot("Plot");
		g1.set_style("points");
		if (num == 0) {
			g1.plot_xy(x,y,"Residual Point");
			g1.plot_slope(b, a, "y=0");
		} else {
			g1.plot_xy(x,y,"Point");
			std::string equation = "y=" + std::to_string(b) + "x+" + std::to_string(a);
			g1.plot_slope(b, a, equation);
		}
		sleep(15);
	} catch (GnuplotException ge) {
		std::cout << ge.what() << std::endl;
	}
}

void ListHandler::addToList(int listNum) {
  // get numbers to add
  std::vector<double> numsToAdd;
  std::cout << "Enter number of numbers to add: ";
  int num;
  bool isValid = false;
  while(!isValid){
    std::cin >> num;
    if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Please enter an Integer or Double only." << std::endl;
  }
  else{
    isValid = true;
  }
  }
  isValid = false;
  std::cout << "Enter numbers line by line." << std::endl;

  for (size_t i = 0; i < num; i++) {
    double addNum;
    while(!isValid){
      std::cin >> addNum;
      if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Please enter an Integer or Double only." << std::endl;
    }
    else{
      isValid = true;
    }
    }
    isValid = false;
    numsToAdd.push_back(addNum);
  }

  // add numbers to appropriate list
  for (double &x : numsToAdd) {
    if (listNum == 1) {
      this->list1.push_back(x);
    } else if (listNum == 2) {
      this->list2.push_back(x);
    }
  }
  std::cout << "Numbers added." << std::endl;
}

void ListHandler::removeFromList(int listNum) {
  // get numbers to remove
  std::vector<double> numsToRemove;
  std::cout << "Enter number of numbers to remove: ";
  int num;
  bool isValid = false;
  while(!isValid){
    std::cin >> num;
    if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Please enter an Integer or Double only." << std::endl;
  }
  else{
    isValid = true;
  }
  }
  isValid = false;
  std::cout << "Enter numbers line by line." << std::endl;
  for (size_t i = 0; i < num; i++) {
    double removeNum;
    while(!isValid){
      std::cin >> removeNum;
      if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Please enter an Integer or Double only." << std::endl;
    }
    else{
      isValid = true;
    }
    }
  isValid = false;
    numsToRemove.push_back(removeNum);
  }

  // remove numbers from appropriate list
  for (double &x : numsToRemove) {
    if (listNum == 1) {
      this->list1.erase(std::remove(this->list1.begin(), this->list1.end(), x), this->list1.end());
    } else if (listNum == 2) {
      this->list2.erase(std::remove(this->list2.begin(), this->list2.end(), x), this->list2.end());
    }
  }
  std::cout << "Numbers removed." << std::endl;
}

void ListHandler::removeAll(int listNum) {
  if (listNum == 1) {
    this->list1.clear();
  } else if (listNum == 2) {
    this->list2.clear();
  }
}

std::ostream &operator<<(std::ostream &os, ListHandler &lh) {
  //print list1
  std::vector<double> list1 = lh.allNums1();
  std::vector<double> list2 = lh.allNums2();
  os << "List 1: ";
  bool hasStuff = false;
  for (double &x : list1) {
    hasStuff = true;
    os << x << " ";
  }
  if (!hasStuff) {
    os << "empty";
  }
  hasStuff = false;
  os << "\n";

  //print list2
  os << "List 2: ";
  for (double &y : list2) {
    hasStuff = true;
    os << y << " ";
  }
  if (!hasStuff) {
    os << "empty";
  }
  hasStuff = false;
  os << "\n";

  return os;
}

// Non-class functions

void printHelp() {
	// add
  std::cout << "add" << std::endl;
	std::cout << " -Use to add values to list 1 or 2" << std::endl;
	// remove
	std::cout << "remove" << std::endl;
	std::cout << "\t -Use to remove values from list 1 or 2" << std::endl;
	// removeAll
	std::cout << "removeAll" << std::endl;
	std::cout << "\t -Use to entirely empty list 1 or 2" << std::endl;
	// print
	std::cout << "print" << std::endl;
	std::cout << "\t -Use to print both lists" << std::endl;
	// help
	std::cout << "help" << std::endl;
	std::cout << "\t -Use to see commands" << std::endl;
	// end
	std::cout << "end" << std::endl;
	std::cout << "\t -Use to close calculator" << std::endl;
	// stats
	std::cout << "stats" << std::endl;
	std::cout << "\t -Use to view basic stats on list 1 or 2" << std::endl;
	// compare
	std::cout << "compare" << std::endl;
	std::cout << "\t -Use to compare lists 1 and 2" << std::endl;
	// plot
	std::cout << "plot" << std::endl;
	std::cout << "\t -Use to plot list 1 (x) vs. list 2 (y)" << std::endl;
	// linregplot
	std::cout << "linregplot" << std::endl;
	std::cout << "\t -Use to plot list 1 (x) vs. list 2 (y) with line of best fit" << std::endl;
	// plot
	std::cout << "resplot" << std::endl;
	std::cout << "\t -Use to plot residuals" << std::endl;
	// isValueLikely
	std::cout << "isValueLikely" << std::endl;
	std::cout << "\t -Use to see if value is likely to occur in list 1 or 2" << std::endl;
	// linreg
	std::cout << "linreg" << std::endl;
	std::cout << "\t -Use to see linear regression statistics, including equation for line of best fit and R-squared value" << std::endl;

}

int getListNumber() {
  int num;
  bool notValid = true;
  while (notValid) {
    std::cout << "Enter number of list you want (1 or 2): ";
    bool isValid = false;
    while(!isValid){
      std::cin >> num;
      if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Please enter an Integer or Double only." << std::endl;
    }
    else{
      isValid = true;
    }
    }
    isValid = false;
    if (num == 1 || num == 2) {
      notValid = false;
    } else {
      std::cout << "Not a valid list number." << std::endl;
    }
  }
  return num;
}

double getNumber() {
  double num;
  std::cout << "Enter number to test: ";
  bool isValid = false;
  while(!isValid){
    std::cin >> num;
    if(std::cin.fail()){
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Please enter an Integer or Double only." << std::endl;
  }
  else{
    isValid = true;
  }
  }
  isValid = false;
  return num;
}

int main() {
  ListHandler lh = ListHandler();
  bool running = true;

  // while loop: calculator runs infinitely until quit
  while (running) {
    std::string startingStr;
    std::cout << "Enter command or 'help' for list of commands. ";
    std::cin >> startingStr;
    int listNum;
    double testNum;

    if (startingStr == "add") {
      listNum = getListNumber();
      lh.addToList(listNum);
    } else if (startingStr == "remove") {
      listNum = getListNumber();
      lh.removeFromList(listNum);
    } else if (startingStr == "removeAll") {
      listNum = getListNumber();
      lh.removeAll(listNum);
    } else if (startingStr == "print") {
      std::cout << lh;
    } else if (startingStr == "help") {
      printHelp();
    } else if (startingStr == "end") {
      std::cout << "Closing statistics application. Goodbye." << std::endl;
      running = false;
    } else if (startingStr == "stats") {
      listNum = getListNumber();
      if(listNum == 1){
        lh.statsOf1(true);
      }
      else{
        lh.statsOf2(true);
      }
    } else if (startingStr == "compare") {
      lh.compare();
    } else if (startingStr == "isValueLikely") {
      listNum = getListNumber();
      testNum = getNumber();
      if(listNum == 1){
        lh.isLikely1(testNum);
      }
      else{
        lh.isLikely2(testNum);
      }
    } else if (startingStr == "linreg") {
      lh.createLinearRegression();
    } else if (startingStr == "plot") {
      lh.plot();
    } else if (startingStr == "resplot") {
			lh.createLinearRegression();
			std::vector<double> line;
			line.push_back(0.0);
			line.push_back(0.0);
      lh.plotWithLine(0, line);
    } else if (startingStr == "linregplot") {
			std::vector<double> line = lh.createLinearRegression();
      lh.plotWithLine(1, line);
    } else {
      std::cout << "Invalid command; please try again." << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}

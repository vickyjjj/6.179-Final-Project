#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <cmath>

// 6.179 Final Project January 2018
// Colin Chaney and Victoria Juan

class ListHandler{
	std::vector<double> list1;
	double total1 = 0;
	double mean1 = 0;
	double standardErrorSum1 = 0;
	double standardDeviation1 = 0;
	double variance1 = 0;
	double max1 = 0;
	double min1 = 0;
	double median1 = 0;

	std::vector<double> list2;
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

				max1 = list1[list1.size() - 1];
				min1 = list1[0];

				if(list1.size() % 2 == 0){
					median1 = (list1[(list1.size()-1)/2 + 1] + list1[(list1.size() - 1) / 2])/2;
				}
				else{
					median1 = list1[(list1.size() - 1 )/ 2];
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

				max2 = list2[list2.size() - 1];
				min2 = list2[0];

				if(list2.size() % 2 == 0){
					median2 = (list2[(list2.size()-1)/2 + 1] + list2[(list2.size() - 1) / 2])/2;
				}
				else{
					median2 = list2[(list2.size() - 1 )/ 2];
				}
				if(printOut){
					std::cout << "Mean: " << mean2 << "    Standard Error: " << standardErrorSum2 << "    Standard Deviation: " << standardDeviation2 << std::endl << "Variance: " << variance2 <<  "    Min: " << min2 << "    Median: " << median2 << "    Max: " << max2 <<  std::endl;
				}
			}
		}

		void sortList1(){
	    	int n = list1.size();
	    	int min = 0;
	    	double tempNumber = 0;
	    	for(int j = 0; j < n-1; j++){

	        	min = j;

	        	for(int i = j+1; i < n; i++){
	            	if(list1[i] < list1[min]){
	            	   	min = i;
	           		 }
	    		}

	    		if(min != j){
	            	tempNumber = list1[j];
	            	list1[j] = list1[min];
	           		list1[min] = tempNumber;
	        	}
	    	}
	}

	void sortList2(){
    	int n = list2.size();
    	int min = 0;
    	double tempNumber = 0;
    	for(int j = 0; j < n-1; j++){

        	min = j;

        	for(int i = j+1; i < n; i++){
            	if(list2[i] < list2[min]){
               		min = i;
            	}

    		}

    		if(min != j){
            	tempNumber = list2[j];
            	list2[j] = list2[min];
           		list2[min] = tempNumber;
        	}
    	}
	}
};

int main(){
	std::vector<double> test; 
	test.push_back(10);
	test.push_back(14.5);
	test.push_back(4.6);
	test.push_back(6.8);

	ListHandler ListHandlerTest = *(new ListHandler());
	ListHandlerTest.assignList1(test);
	ListHandlerTest.statsOf1(true);


	std::cout << std::endl;


	std::vector<double> test3;

	ListHandlerTest.assignList2(test3);
	ListHandlerTest.statsOf2(true);

	//statsOf(test);
	return 0;
}
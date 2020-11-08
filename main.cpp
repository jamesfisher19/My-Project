#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

//Declare functions
float compute_gross_pay(int, float, char); //function prototypes
float compute_taxes(float);
float compute_net_pay(float, float);
void print_pay_check(string, string, string, int, string, string, string, string , int ,
float, float, float);
float compute_federal_tax(float);
float compute_state_tax(float);
float compute_city_tax(float);
//Date
const string date = "02/14/2020";


void print_pay_check(string last_name, string first_name, string street_name, int address_num, string street_type, string city, string state, int zip , float grossPay, float totalTax, float netPay){
  
  ofstream myOutfile("outputfile.txt",ios_base::app);//Write into existing file


    myOutfile << "**************************************************************************" << endl 
    << "ABC Flowers" << endl
    << "123 Georgia Ave" << "                                  " << date << endl
    << "Washington, DC 20059" << endl
    << " " << endl
    
    << "Payable to: " << last_name << " " << first_name << "            " << "Pay this amount: $" << fixed << setprecision(2) << netPay << endl
    << "            "<< address_num << " " << street_name << " " << street_type << endl
    << " " << "           " << city << " " << state << " "<< zip << "                   " << " " << endl
    << "Gross Pay: $"  << grossPay << endl 
    << "Total Taxes: $" << totalTax << endl;
		myOutfile.close();

}

//Main Function
int main()
{
  string NAME, DED, ID, ADDRESS, CITY_ST, ZIP_RATE, F_P, RATE ;
  int line; //declare variables
  char parttime_fulltime;
  float payRate;
  float grossPay;
  float netPay;
  float totalTax;

  //Declare variables;
  string last_name, first_name, street_name, street_type, city, state;
  int zip, deductions, employee_id, address_num;


  ifstream myfile;
  //ofstream outfile;

  // open infile;
  myfile.open("inputfile.txt");


  // INSERT THE CODE TO READ THE FIRST LINE OF THE FILE
  myfile >> NAME >> DED >> ID >> ADDRESS >>
  CITY_ST >> ZIP_RATE >> RATE >> F_P;

  //Read rest of file

  line = 1;
  while (line < 7) {

    myfile >> last_name >> first_name >> deductions >> employee_id >> address_num >>
    street_name >> street_type >> city >> state >> zip >> payRate >> parttime_fulltime;  
  
    grossPay = compute_gross_pay(deductions, payRate, parttime_fulltime);
    totalTax = compute_taxes(grossPay);
    netPay = compute_net_pay(totalTax, grossPay);

    print_pay_check(last_name,  first_name,  street_name,  address_num,  street_type,  city,  state, zip,  grossPay,  totalTax,netPay);
    line++;
  }
  myfile.close();


  //outfile.close();
  return 0; // return 0 if everything works fine
}


//ComputeGrossPay
float compute_gross_pay(int deductions, float payRate, char parttime_fulltime ) {
  float grossPay;
  if (parttime_fulltime == 'P') 
  {
      grossPay = (40 * payRate) + (10.50 * deductions);
  }
    else if (parttime_fulltime == 'F')
  {
      grossPay = (40 * payRate); 
  }
  return grossPay;

  }


//ComputeFederalTax
float compute_federal_tax(float grossPay){
  float fed_tax ;
  float fed_tax1, fed_tax2, fed_tax3;
  if (grossPay <= 200) {
    fed_tax1  = .15 * grossPay;
    fed_tax = fed_tax1;
  }
    else if (grossPay > 200 && grossPay <= 500){
      fed_tax2 = (.15 * 200) + (.25 * (grossPay -200));
      fed_tax = fed_tax2;
    }
      else if (grossPay > 500){
          fed_tax3 = (.15 * 200) + (.25 * 300) + (.35 * (grossPay - 500));
          fed_tax = fed_tax3;
      }
  return fed_tax;
}





//ComputeStateTax
float compute_state_tax(float fed_tax){
  float state_tax;
  if (fed_tax >= 80) 
  {
    state_tax = 0;
  }
  else if (fed_tax < 80)
    {
      state_tax = 0.10 * fed_tax;
    }
  return state_tax;
}

//ComputeCityTax
float compute_city_tax(float state_tax) {
   float city_tax;
   if (state_tax >= 50){
     city_tax = 0;
   }
   else if (state_tax < 50)
   {
     city_tax = 0.08 * state_tax;
   }
  return city_tax;
}

//ComputeTotalTaxes
float compute_taxes(float grossPay) {
  float totalTax;
  float fed_tax;
  float state_tax;

  totalTax = compute_federal_tax(grossPay) + compute_state_tax(fed_tax) + compute_city_tax(state_tax);
  return totalTax;
}

//ComputeNetPay
float compute_net_pay(float totalTax, float grossPay){
  float netPay;
  netPay = grossPay - totalTax;
  return netPay;
}


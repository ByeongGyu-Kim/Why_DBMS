#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct customer {
  char LNAME[20];
  int ZONE;
  int ACTIVE;
};

struct zonecost {
  int ZONEID;
  char ZONEDESC[20];
};

struct lineitem {
  char UNAME[20];
  char DATE[10];
  char TIME[10];
  int BARCODE;
  int QUANTITY;
  float PRICE;
};

struct product {
  int BARCODE;
  char PRODDESC[50];
};

int main(int argc, char** argv) {
  if (argc != 4) {
    return 0;
  }

  if (!strcmp(argv[1], "q1")) {
    for (int i = 1; i < 6; i++) {
      ifstream customer_file;
      string customer_file_name = "./q1/";
      customer_file_name += to_string(i) + "/";
      customer_file_name += argv[2];

      ifstream zonecost_file;
      string zonecost_file_name = "./q1/";
      zonecost_file_name += to_string(i) + "/";
      zonecost_file_name += argv[3];

      ofstream outfile;
      string outfile_name = "./q1/";
      outfile_name += to_string(i);
      outfile_name += "/result1.txt";
		outfile.open(outfile_name);

	  
      customer_file.open(customer_file_name);
      string line;
      int customer_line_cnt = 0;
      while (!customer_file.eof()) {
        getline(customer_file, line);
        customer_line_cnt++;
      }
      customer_line_cnt -= 3;
      customer_file.close();
      customer_file.open(customer_file_name);
      getline(customer_file, line);
      getline(customer_file, line);

      zonecost_file.open(zonecost_file_name);
      int zonecost_line_cnt = 0;
      while (!zonecost_file.eof()) {
        getline(zonecost_file, line);
        zonecost_line_cnt++;
      }
      zonecost_line_cnt -= 3;
      zonecost_file.close();
      zonecost_file.open(zonecost_file_name);
      getline(zonecost_file, line);
      getline(zonecost_file, line);

      customer* customers = new customer[customer_line_cnt];
      for (int a = 0; a < customer_line_cnt; a++) {
        string str;
        getline(customer_file, str);
        
        for (int b = 0; b < 20; b++) {
          customers[a].LNAME[b] = str[b + 42];
        }

        string zone;
        for (int b = 0; b < 6; b++) {
          zone += str[b + 135];
        }
        customers[a].ZONE = stoi(zone);

        string active;
        for (int b = 0; b < 6; b++) {
          active += str[b + 243];
        }
        customers[a].ACTIVE = stoi(active);
      }
      customer_file.close();

      zonecost* zonecosts = new zonecost[zonecost_line_cnt];
      for (int a = 0; a < zonecost_line_cnt; a++) {
        string str;
        getline(customer_file, str);

        string zoneid;
        for (int b = 0; b < 6; b++) {
          zoneid += str[b];
        }
        zonecosts[a].ZONEID = stoi(zoneid);

        for (int b = 0; b < 20; b++) {
          zonecosts[a].ZONEDESC[b] = str[b + 7];
        }
      }
      zonecost_file.close();

      string toronto = "Toronto";
      string char2str = "";
      int zoneid_array[zonecost_line_cnt];
      for (int a = 0; a < zonecost_line_cnt; a++) {
        zoneid_array[a] = 0;
      }

      int toronto_cnt = 0;
      for (int a = 0; a < zonecost_line_cnt; a++) {
        for (int b = 0; b < 20; b++) {
          char2str.push_back(zonecosts[a].ZONEDESC[b]);
        }
        if (toronto == char2str) {
          zoneid_array[toronto_cnt] = zonecosts[a].ZONEID;
          toronto_cnt++;
        } else {
          char2str = "";
          continue;
        }
      }

      for (int a = 0; a < customer_line_cnt; a++) {
        for (int b = 0; b < toronto_cnt; b++) {
          if (customers[a].ZONE == zoneid_array[toronto_cnt]) {
            if (customers[a].ACTIVE == 1) {
              for(int c = 0; c < 20; c++){
				outfile << customers[a].LNAME[c];
			  }
			  outfile << endl;
            }
          }
        }
      }
      outfile.close();
    }
    return 0;
  }

  else if (!strcmp(argv[1], "q2")) {
    for (int i = 1; i < 6; i++) {
      ifstream lineitem_file;
      string lineitem_file_name = "./q2/";
      lineitem_file_name += to_string(i) + "/";
      lineitem_file_name += argv[2];

      ifstream products_file;
      string products_file_name = "./q2/";
      products_file_name += to_string(i) + "/";
      products_file_name += argv[3];

      ofstream outfile;
      string outfile_name = "./q2/";
      outfile_name += to_string(i);
      outfile_name += "/result1.txt";

      lineitem_file.open(lineitem_file_name);
      string line;
      int lineitem_file_cnt = 0;
      while (!lineitem_file.eof()) {
        getline(lineitem_file, line);
        lineitem_file_cnt++;
      }
      lineitem_file_cnt -= 3;
      lineitem_file.close();
      lineitem_file.open(lineitem_file_name);
      for (int c = 0; c < 2; c++) {
        getline(lineitem_file, line);
      }

      products_file.open(products_file_name);
      int products_file_cnt = 0;
      while (!products_file.eof()) {
        getline(products_file, line);
        products_file_cnt++;
      }
      products_file_cnt -= 3;
      products_file.close();
      products_file.open(products_file_name);
      for (int c = 0; c < 2; c++) {
        getline(products_file, line);
      }

      lineitem* lineitems = new lineitem[lineitem_file_cnt];
      for (int a = 0; a < lineitem_file_cnt; a++) {
        string str;
        getline(lineitem_file, str);
        for (int b = 0; b < 20; b++) {
          lineitems[a].UNAME[b] = str[b];
        }

        for (int b = 0; b < 10; b++) {
          lineitems[a].DATE[b] = str[b + 21];
        }

        for (int b = 0; b < 8; b++) {
          lineitems[a].TIME[b] = str[b + 32];
        }

        string barcode;
        for (int b = 0; b < 20; b++) {
          barcode += str[b + 41];
        }
        lineitems[a].BARCODE = stoi(barcode);

        string quantity;
        for (int b = 0; b < 8; b++) {
          quantity += str[b + 62];
        }
        lineitems[a].QUANTITY = stoi(quantity);

        string price;
        for (int b = 0; b < 9; b++) {
          barcode += str[b + 71];
        }
        lineitems[a].PRICE = stof(price);
      }
      lineitem_file.close();

      product* products = new product[products_file_cnt];
      for (int a = 0; a < lineitem_file_cnt; a++) {
        string str;
        getline(products_file, str);

        string barcode;
        for (int b = 0; b < 20; b++) {
          barcode += str[b];
        }
        products[a].BARCODE = stoi(barcode);

        for (int b = 0; b < 50; b++) {
          products[a].PRODDESC[b] = str[b + 32];
        }
      }
      products_file.close();

      int lineitem_2darray[lineitem_file_cnt][2];
      for (int a = 0; a < lineitem_file_cnt; a++) {
        for (int b = 0; b < 2; b++) {
          lineitem_2darray[a][b] = 0;
        }
      }

      int barcode_cnt = 0;
      for (int a = 0; a < lineitem_file_cnt; a++) {
        int barcode = products[a].BARCODE;
        int b;
        for(b = 0; b < barcode_cnt; b++){
          if(barcode == lineitem_2darray[b][1]){
            lineitem_2darray[b][1] += 1;
            break;
          }
        }
        if(b == barcode_cnt){
          lineitem_2darray[b][1] = 1;
          barcode_cnt++;
        }
      }

      for(int a = 0; a < barcode_cnt; a++){
          if(lineitem_2darray[a][1] >= 2){
            for(int b = 0; b < products_file_cnt; b++){
              if(lineitem_2darray[a][1] == products[b].BARCODE){

              }
            }
          }
      }


    }
    return 0;
  }

  return 0;
}

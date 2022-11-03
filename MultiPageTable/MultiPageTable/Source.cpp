#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <math.h>
using namespace std;

typedef struct _page_table_1 {


    int array[4];
    

} page_table_1;

typedef struct _page_table_2 {


    int array[4];


} page_table_2;

typedef struct _fake_page_frame {
    int array[4];

}fake_page_frame;

class MLPT {

private:
    int page_Frame_size; 
    int RAM_amount;
    int total_size_per_process;
    int program_counter;
    const int page_frame_amount = int(256 / 48);
    string * program_trakcer_array;
    fake_page_frame * page_frame_array;
    page_table_1 * page1_table;
    page_table_2 * page2_table;
    
    

public:
    MLPT() {
        total_size_per_process = sizeof(fake_page_frame) + sizeof(page_table_1) + sizeof(page_table_2);
        int page_Frame_size = 4;
        int RAM_amount = 256;
        const int max_program_amount = int(256 / 48);
        page_frame_array =  new fake_page_frame[max_program_amount];
        page1_table = new page_table_1[max_program_amount];
        page2_table = new page_table_2[max_program_amount];
        //16 bits is the array size;
        this->program_counter = 0;
        program_trakcer_array = new string[max_program_amount];

    }
    ~MLPT() {
        delete program_trakcer_array;
        delete page1_table;
        delete page2_table;
        delete page_frame_array;
    }

    void allocate(string program)
    {
        if (program_counter > 5) {
            printf("out of memory\n");
        }
        //int value = stoi(program) % 5;
    
        
        program_trakcer_array[program_counter] = program;
        
        int inside_arraycounter = 0; 

        for (int i = 0; i < 4; i++) {
            page1_table[program_counter].array[i] = inside_arraycounter;
            page2_table[program_counter].array[i] = inside_arraycounter;
            page_frame_array[program_counter].array[i] = inside_arraycounter;
            inside_arraycounter++;
        }
        program_counter++;


      
    }
    int translate(string fake_number, string program)

    {
        stringstream ss;
        ss << hex << fake_number;
        unsigned n;
        ss >> n;
        bitset<8> b(n);
        int offset = 0;
        int page_level_1 = 0;
        int page_level_2 = 0; 
        
        for (int i = 0; i < 8; i++) {
            if (i < 2) {
                offset += b[i] * pow(2, i);
            }
            else if (i < 5) {
                page_level_2 += b[i] * pow(2, i);
            
            }
            else {
                page_level_2 = b[i] * pow(2, i);
            }
        
        }  
  
        for (int k = 0; k < 5; k++) {
            if (program == program_trakcer_array[k]) {
                int temp1 = page1_table[k].array[page_level_1];
                int temp2 = page2_table[temp1].array[page_level_2];

                return page_frame_array[temp2].array[offset];
            }
        }
        printf("no program was found \n");
        return 1;
        
    }

};


int main() {
    
    MLPT mlpt;
    mlpt.allocate("test");
    mlpt.allocate("something");
   
    printf("%d \n", mlpt.translate("0X1A", "test"));
    printf("%d ", mlpt.translate("0X10", "something"));
    printf("%d \n", mlpt.translate("0X10", "test"));

   

}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <array>
#include <bits/stdc++.h>
#include <limits.h>
#include <stdlib.h>
#include <unordered_set>
#define N 3
class IntcodeComputer{
    public:
        IntcodeComputer(const std::vector<int>& program){ //takes in the "program/code" can continue to be vector
            this->initial_program = program;
            this->program = program;
        }
        void reset(){
            program = initial_program; 
            complete = true;
            ip = 0;
            relative_base = 0; //starts at 0

        }
        int interpret(int ip, int param, int offset)
        {
            if(param == 0) //
            {
                return program[ip];
            }
            else if(param == 1)//position
            {
                return ip;
            }
            else{
                return program[relative_base+offset];
            }
            
        }
        int compute(const std::vector<int> &input)
        {    
            int mode = 0; //if mode = 0, then position mode, if mode = 1 then immediate mode
            int output = -1;
            int input_ptr = 0;
            while(program[ip]!=99)
            {
                //program[ip] is a max 5 digit number which needs to be parsed to be 3 digit position par and 2 digit ip
                int op = program[ip]%100;
                int x = program[ip];
                int p1 = interpret(ip+1, (x/100)%10, program[ip+1]);
                int p2 = interpret(ip+2, (x/1000)%10, program[ip+2]);
                int p3 = interpret(ip+3, (x/10000)%10, program[ip+3]);
            
                if(op== 1){
                    program[p3] = program[p1] + program[p2];
                    ip+=4;
                }
                else if(op == 2)
                {
                
                    program[p3] = program[p1] * program[p2];
                    ip+=4;

                }
                
                else if(op == 3)
                {

                    program[p1] = input[input_ptr];
                    input_ptr+=1;
                    ip+=2;
                }
                else if(op==4)
                {
                    output = program[p1]; //parameter
                    ip+=2;
                    return output;
                }

                else if(op == 5)
                {
                    if(program[p1]!= 0)
                    {
                        ip = program[p2];
                    }
                    else
                    {
                        ip+=3;
                    }
                }
                else if(op == 6)
                {
                    if(program[p1] == 0)
                    {
                        ip = program[p2];
                    }
                    else{
                        ip+=3;
                    }
                }
                else if(op == 7)
                {
                    program[p3] = program[p1] < program[p2];
                    ip+=4;
                }
                else if(op ==8)
                {
                    program[p3] = program[p1] == program[p2];
                    ip+=4;
                }
                else if(op == 9){
                    relative_base += p1;
                    ip+=2;
                }
            
            }
            complete = true;
            return output;
        }
        bool isComplete() {return complete;}
    private:
        std::vector<int> program;
        std::vector<int> initial_program;
        bool complete = false;
        int ip = 0;
        int relative_base;
};
//gonna have 5! different non repeating  combinations. need to use dfs/backtracking to sovle problem
void dfs(std::unordered_set<int> hset, std::vector<std::vector<int>>& combinations,std::vector<int> vec){
    //base case
    if(hset.size() == 0){
        //append vector to combinations
        combinations.push_back(vec);
        return;
    }
    for(auto element: hset){
        std::vector<int> v2 = vec;
        std::unordered_set<int> set2 = hset;
        v2.push_back(element);
        set2.erase(element);
        dfs(set2,combinations,v2);
    }
}

void convert_to_vector(std::vector<int> &outputs, std::string content)
{
    std::stringstream ss1(content);
    while (ss1.good())
    {
        std::string substr;
        std::getline(ss1, substr, ',');
        int num = stoi(substr);
        outputs.push_back(num);
    }
}
int test_amplifier_configuration(IntcodeComputer& computer, std::vector<int>& phase_setting){
    int initial = 0;
    for(int i = 0; i < phase_setting.size(); i ++){
        int phase = phase_setting[i];
        initial = computer.compute(std::vector<int>{phase_setting[i], initial});
        computer.reset();
    }
    return initial;
}
int main()
{
    std::fstream data("seven.txt");
    std::string str;
    std::vector<int> input; 
    std::getline(data, str);
    convert_to_vector(input, str);

    std::unordered_set<int> hset = {0,1,2,3,4}; //this will be passed into every dfs func
    std::vector<std::vector<int>> combinations;
    std::vector<int> vec; //this will be appended into combinations 
    dfs(hset, combinations,vec); 
    int max = INT_MIN;
    IntcodeComputer computer(input); 


    for(auto outer: combinations){
    
        int initial = test_amplifier_configuration(computer, outer);
        if(initial > max){
            max = initial;
        }
    }
    std::cout<< max << std::endl;


    //PART B
        
    //

    
}


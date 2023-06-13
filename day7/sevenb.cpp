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
void convert_to_vector(std::vector<int> &outputs, std::string content);
int interpret(int ip, int param, int array[]);
int computer(int array[],int size, int in1, int in2, int &ip, bool phaseTrue);
void permute(std::unordered_set<int> hset, std::vector<std::vector<int>>& combinations,std::vector<int> vec);
int main()
{
    std::fstream data("seven.txt");
    std::string str;
    std::vector<int> input; 
    std::getline(data, str);
    convert_to_vector(input, str);
    int size = input.size();
    int code[size];
    int holder[size];
    for(int i = 0; i < size; i ++)
    {
        code[i] = input.at(i);
        holder[i] = input.at(i);
    }
    //we have value in code
    //find all combinations of 5 [0,0,0,0,0] //perhaps 2d array
    std::unordered_set<int> hset = {5,6,7,8,9}; //this will be passed into every permute func
    std::vector<std::vector<int>> combinations;
    std::vector<int> vec; //this will be appended into combinations 
    //computer(code, size); //first phase setting then initial input = 0
    permute(hset, combinations,vec);
    int max = INT_MIN;
    std::vector<int> ips = {0,0,0,0,0}; //keep track of instruction pointers to resume where started
    std::vector<int> test={9,8,7,6,5};
    int initial = 0;
    for(int i = 0; i < test.size(); i ++){
        int phase = test[i];
        initial = computer(code,size,phase,initial, ips[i], true);
    
    }
    std::cout << initial << std:: endl;
    while(code[ips[4]]!=99){
        //now output of E must go into A and not the phase settings
        //initial = output[E]
        for(int i = 0; i < test.size(); i ++){
            int phase = test[i];
            initial = computer(code,size,phase,initial, ips[i], false);
        }
    } 
    //do while compE[ip] != 99 //does not hault
    //INI
    // for(int i = 0; i < test.size(); i ++){
    //     int phase = test[i];
    //     initial = computer(code,size,phase,initial);
    // }
    
    std::cout<< max << std::endl;


    
}
//gonna have 5! different non repeating  combinations. need to use permute/backtracking to sovle problem

int computer(int array[],int size, int in1, int in2, int &ip, bool phaseTrue)
{    
    int mode = 0; //if mode = 0, then position mode, if mode = 1 then immediate mode
    int output;
    bool secondIn = false;
    while(array[ip]!=99)
    {
        //array[ip] is a max 5 digit number which needs to be parsed to be 3 digit position par and 2 digit ip
        int op = array[ip]%100;
        int x = array[ip];
        int p1 = interpret(ip+1, (x/100)%10, array);
        int p2 = interpret(ip+2, (x/1000)%10, array);
        int p3 = interpret(ip+3, (x/10000)%10, array);
    
        if(op== 1)
        {
            
            array[p3] = array[p1] + array[p2];
            ip+=4;

        }
        else if(op == 2)
        {
           
            array[p3] = array[p1] * array[p2];
            ip+=4;

        }
        
        else if(op == 3)
        {
            if(phaseTrue){
                if(!secondIn){
                    array[p1] = in1;
                    secondIn = true;
                }
                else{
                    array[p1] = in2;
                }
            }
            else{
                array[p1] = in2;
            }
            ip+=2;
        }
        else if(op==4)
        {
            output = array[p1]; //parameter
            std::cout << output << std::endl;
            ip+=2;
            return output; //forces to wait, need to remember ip tho
        }

        else if(op == 5)
        {
            if(array[p1]!= 0)
            {
                ip = array[p2];
            }
            else
            {
                ip+=3;
            }
        }
        else if(op == 6)
        {
            if(array[p1] == 0)
            {
                ip = array[p2];
            }
            else{
                ip+=3;
            }
        }
        else if(op == 7)
        {
            
            
            array[p3] = array[p1] < array[p2];
            ip+=4;
        }
        else if(op ==8)
        {
            
            array[p3] = array[p1] == array[p2];
            ip+=4;
        }
    
    }

    return output;
    
}
int interpret(int ip, int param, int array[])
{
    if(param == 0)
    {
        return array[ip];
    }
    else
    {
        return ip;
    }
}

void permute(std::unordered_set<int> hset, std::vector<std::vector<int>>& combinations,std::vector<int> vec){
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
        permute(set2,combinations,v2);
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
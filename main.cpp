/*
*Convert RGB-D Scenes dataset v2 to TUM RGB-D format
*Author: Xiao Han
*github: github.com/Xiao-Han99
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <strstream>
#include <sstream>
#include <unistd.h>

using namespace std;

void ConvertImg(const string path,const string num,int numlines)
{
    cout<<endl<<"Convert Images, please wait ..."<<endl;
    //copy png
    string command;
    command = "mkdir -p " + path + "/rgb";  
    system(command.c_str());
    command = "mkdir -p " + path + "/depth";  
    system(command.c_str());

    double timestamp = 0.0;
    for(int i=0;i<numlines;i++)
    {   

        strstream OutnameStream;
        OutnameStream <<fixed<<timestamp;
        string out_name;
        OutnameStream >> out_name;

        strstream nameStream;
        nameStream <<setfill('0')<<setw(5)<<i;
        string origin_name;
        nameStream >> origin_name;
        
        command = "cp -f "+path+"/scene_"+num+"/"+origin_name+"-color.png " + path+"/rgb/"+out_name+".png";
        system(command.c_str());
        usleep(1000);
        command = "cp -f "+path+"/scene_"+num+"/"+origin_name+"-depth.png " + path+"/depth/"+out_name+".png";
        system(command.c_str());
        usleep(1000);

        timestamp += 0.05;
    }

}

void CreateTxt(const string path,const string num,int numlines)
{
    cout<<"CreateTxt: rgb.txt depth.txt associations.txt"<<endl;
    ofstream outfile_rgb;
    outfile_rgb.open(path + "/rgb.txt");
    if(!outfile_rgb.is_open())
        cerr <<"outfile_rgb error "<<endl;
    outfile_rgb << fixed;
    
    ofstream outfile_depth;
    outfile_depth.open(path + "/depth.txt");
    if(!outfile_depth.is_open())
        cerr <<"outfile_depth error "<<endl;
    outfile_depth << fixed;

    ofstream outfile_associate;
    outfile_associate.open(path + "/associations.txt");
    if(!outfile_associate.is_open())
        cerr <<"outfile_associate error "<<endl;
    outfile_associate << fixed;

    outfile_rgb <<"# color images"<<endl;
    outfile_rgb <<"# file: "<<path<<endl;
    outfile_rgb <<"# timestamp filename"<<endl;

    outfile_depth <<"# depth maps"<<endl;
    outfile_depth <<"# file: "<<path<<endl;
    outfile_depth <<"# timestamp filename"<<endl;

    double timestamp = 0;
    
    for(int i=0;i<numlines;i++)
    {
        outfile_rgb<< timestamp <<" rgb/"<<timestamp<<".png"<<endl;
        outfile_depth << timestamp << " depth/"<<timestamp<<".png"<<endl;
        outfile_associate << timestamp << " rgb/"<<timestamp<<".png " <<timestamp<<" depth/"<<timestamp<<".png"<<endl;
        
        timestamp += 0.05;
    }

    outfile_rgb.close();
    outfile_depth.close();
    outfile_associate.close();

}



void CreateGT(const string path,const string num)
{
    cout<<"Create GT file"<<endl;
    ifstream pose;
    pose.open(path + "/"+ num +".pose");
    if(!pose.is_open())
        cerr << "open pose file error"<<endl;

    ofstream outfile_GT;
    outfile_GT.open(path + "/groundtruth.txt");
    if(!outfile_GT.is_open())
        cerr <<"outfile_GT error "<<endl;
    outfile_GT << fixed;
    outfile_GT <<"# ground truth trajectory"<<endl;
    outfile_GT <<"# file: "<<path<<endl;
    outfile_GT <<"# timestamp tx ty tz qx qy qz qw"<<endl;


    double timestamp = 0;
    while(!pose.eof())
    {
        string s;
        getline(pose,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;

            double x,y,z,qx,qy,qz,qw;
            ss >> qw;
            ss >> qx;
            ss >> qy;
            ss >> qz;
            ss >> x;
            ss >> y;
            ss >> z;

            outfile_GT << timestamp << " "<<x<<" "<< y <<" "<<z<<" "<<qx<<" "<<qy<<" "<<qz<<" "<<qw<<endl;
            timestamp += 0.05;
        }

    }
    pose.close();
    outfile_GT.close();
}



int main(int argc, char **argv)
{

    if(argc != 3)
    {
        cerr << endl << "Usage: ./ConvertRGBD path_to_sequence sequence_number" << endl;
        return 1;
    }

    string path = string(argv[1]);
    string number = string(argv[2]);

    ifstream pose;
    pose.open(path + "/" + number + ".pose");
    if(!pose.is_open())
        cerr << "open pose file error"<<endl;

    int numlines = 0;
    std::string line;
    while (getline(pose,line))
        ++numlines;
    pose.close();

    ConvertImg(path,number,numlines);

    CreateTxt(path,number,numlines);

    CreateGT(path,number);

    cout<<"successful convert "<<number<<" to TUM"<<endl;

}

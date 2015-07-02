#include "car_obj.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

Object* import_object(const std::string& filename)
{

	vector<vector<double> > tmp_vertices;

	vector<string> tmp_partnames;
	vector<vector<vector<double> > > tmp_uvs;
	vector<vector<vector<double> > > tmp_normals;
	vector<vector<vector<vector<int> > > > tmp_faces;
	// Open file

	std::ifstream objfile(filename.c_str());
	if(objfile.fail())
	{
		std::cerr<<"Error: could not open file "<<filename<<std::endl;
		// exit(1);
	}

	std::string line;
	int index = -1;
	string vstr;
	string v1,v2,v3;
	double val;
	while(getline(objfile,line))
	{
		
		if(line[0] == 'o')
		{
			index++;
			string pname = line.substr(2);
			tmp_partnames.push_back(pname);
			// std::cerr<<"partname: "<<pname<<std::endl;
			tmp_uvs.resize(index+1);
			tmp_normals.resize(index+1);
			tmp_faces.resize(index+1);
		}
		if(line[0] == 'v' && line[1] == ' ')
		{
			vector<double> tmp_verts;
			vstr = line.substr(2);

			v1 = vstr.substr(0,vstr.find(' '));
			val = atof(v1.c_str());
			// cout<<val<<" ";
			tmp_verts.push_back(val);

			vstr = vstr.substr(v1.length()+1);
			v2 = vstr.substr(0, vstr.find(' '));
			val = atof(v2.c_str());
			// cout<<val<<" ";
			tmp_verts.push_back(val);

			v3 = vstr.substr(v2.length() + 1);
			val = atof(v3.c_str());
			// cout<<val<<endl;
			tmp_verts.push_back(val);

			tmp_vertices.push_back(tmp_verts);
		}
		if(line[0] == 'v' && line[1] == 't')
		{
			vector<double> tmp_uv;

			vstr = line.substr(3);

			v1 = vstr.substr(0,vstr.find(' '));
			val = (double)atof(v1.c_str());
			tmp_uv.push_back(val);

			v2 = vstr.substr(v1.length() + 1, vstr.find(' '));
			val = (double)atof(v2.c_str());
			tmp_uv.push_back(val);

			tmp_uvs[index].push_back(tmp_uv);
		}
		if(line[0] == 'v' && line[1] == 'n')
		{
			vector<double> tmp_nor;
			vstr = line.substr(3);

			v1 = vstr.substr(0,vstr.find(' '));
			val = atof(v1.c_str());
			tmp_nor.push_back(val);

			v2 = vstr.substr(v1.length()+1, vstr.find(' '));
			val = atof(v2.c_str());
			tmp_nor.push_back(val);

			v3 = vstr.substr(v1.length() + v2.length()+2, vstr.find(' '));
			val = atof(v3.c_str());
			tmp_nor.push_back(val);

			tmp_normals[index].push_back(tmp_nor);
		}
		if(line[0] == 'f')
		{
			vector<int> tmp_vis;
			vector<vector<int> > tmp_fs;

			vstr = line.substr(2);
			string str1,str2,str3;

			str1 = vstr.substr(0,vstr.find(' '));
			vstr = vstr.substr(str1.length()+1);
			str2 = vstr.substr(0, vstr.find(' '));
			str3 = vstr.substr(str2.length()+1);

			// cerr<<str1<<" "<<str2<<" "<<str3<<endl;
			v1 = str1.substr(0,str1.find('/'));
			val = (int)atof(v1.c_str())-1;
			tmp_vis.push_back(val);

			str1 = str1.substr(v1.length()+1);
			v2 = str1.substr(0, str1.find('/'));
			val = (int)atof(v2.c_str())-1;
			tmp_vis.push_back(val);

			v3 = str1.substr(v2.length()+1);
			val = (int)atof(v3.c_str())-1;
			tmp_vis.push_back(val);

			tmp_fs.push_back(tmp_vis);
			tmp_vis.clear();

			
			v1 = str2.substr(0,str2.find('/'));
			val = (int)atof(v1.c_str())-1;
			tmp_vis.push_back(val);

			str2 = str2.substr(v1.length()+1);
			v2 = str2.substr(0, str2.find('/'));
			val = (int)atof(v2.c_str())-1;
			tmp_vis.push_back(val);

			v3 = str2.substr(v2.length()+1);
			val = (int)atof(v3.c_str())-1;
			tmp_vis.push_back(val);

			tmp_fs.push_back(tmp_vis);
			tmp_vis.clear();

			
			// cerr<<str3;
			v1 = str3.substr(0,str3.find('/'));
			val = (int)atof(v1.c_str())-1;
			// cerr<<" "<<val<<endl;
			tmp_vis.push_back(val);

			str3 = str3.substr(v1.length()+1);
			v2 = str3.substr(0, str3.find('/'));
			val = (int)atof(v2.c_str())-1;
			// cerr<<" "<<val;
			tmp_vis.push_back(val);

			v3 = str3.substr(v2.length()+1);
			val = (int)atof(v3.c_str())-1;
			// cerr<<" "<<val<<endl;
			tmp_vis.push_back(val);

			tmp_fs.push_back(tmp_vis);
			tmp_vis.clear();

			tmp_faces[index].push_back(tmp_fs);
		}
	}

	// for(int i = 0; i < tmp_vertices.size(); i++)
	// {
	// 	cerr<<"Partname: "<<tmp_partnames[i]<<endl;
	// 	cerr<<" vertices "<<i<<" : "<<tmp_vertices[i].size()<<endl;
	// }
	Object* obj =new Object(tmp_vertices);

	// cerr<<tmp_partnames.size()<<endl;
	for(int i = 0; i < tmp_partnames.size(); i++)
	{	
		if(tmp_partnames[i] == "glasses")
		{
			Colour t_kd = Colour(0.05);
			Colour t_ks = Colour(0.8);
			double t_shininess = 120;
			Assembly tmp_assembly = Assembly(tmp_partnames[i],tmp_uvs[i],tmp_normals[i],tmp_faces[i],t_kd,t_ks,t_shininess);
			obj->add_assembly(tmp_assembly);
			continue;
		}
		if(tmp_partnames[i] == "rrtire" ||
			tmp_partnames[i] == "rftire" ||
			tmp_partnames[i] == "lftire" ||
			tmp_partnames[i] == "lrtire")
		{
			Colour t_kd = Colour(0);
			Colour t_ks = Colour(0.1);
			double t_shininess = 50;
			Assembly tmp_assembly  = Assembly(tmp_partnames[i],tmp_uvs[i],tmp_normals[i],tmp_faces[i],t_kd,t_ks,t_shininess);
			obj->add_assembly(tmp_assembly);
			continue;
		}
		if(tmp_partnames[i] == "cartrack")
		{
			Colour t_kd = Colour(0.2);
			Colour t_ks = Colour(0.4);
			double t_shininess = 60;
			Assembly tmp_assembly  = Assembly(tmp_partnames[i],tmp_uvs[i],tmp_normals[i],tmp_faces[i],t_kd,t_ks,t_shininess);
			obj->add_assembly(tmp_assembly);
			continue;
		}
		else
		{
			Colour t_kd = Colour(0);
			Colour t_ks = Colour(0.4);
			double t_shininess = 80;
			Assembly tmp_assembly  = Assembly(tmp_partnames[i],tmp_uvs[i],tmp_normals[i],tmp_faces[i],t_kd,t_ks,t_shininess);
			obj->add_assembly(tmp_assembly);
			continue;
		}	
	}
	// cerr<<obj->get_assembly_size()<<endl;
	return obj;
	// return NULL;
}
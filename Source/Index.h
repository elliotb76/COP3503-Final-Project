#pragma once
#include "TrackList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define CONFIG_FILE "config.txt"
using namespace std;

class Index
{
	string trackIndexLocation_;
	string tracklistIndexLocation_;
	vector<string> directories_;
	vector<int> unusedID_;
	int lastID_;

public:
	Index();
	void initiateIndexFromConfig();
	void writeFieldsToConfig();

	void AddDirectory(string newDirectory) { directories_.push_back(newDirectory); }
	void RemoveDirectory(string rmDirectory);

	TrackList* ReadMainIndex();
	vector<TrackList> ReadTrackListIndex();

	void WriteTrackListIndex(vector<TrackList> in);
	void WriteTrackIndex();
	void UpdateTrackIndex();

	TrackList TrackListFromIDList(vector<int> );

};
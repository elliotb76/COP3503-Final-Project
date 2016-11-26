#pragma once
#include "TrackList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Index
{
	string trackIndexLocation_;
	string tracklistIndexLocation;
	vector<string> directories_;
	vector<int> unusedID_;
	int lastID_;

public:
	Index();
	Index(string newIndexFileLocation);
	void AddDirectory(string newDirectory) { directories_.push_back(newDirectory); }
	void RemoveDirectory(string rmDirectory);
	void UpdateTrackIndex();

	TrackList* ReadMainIndex();
	vector<TrackList>* ReadTrackListIndex();

	void WriteTrackListIndex(vector<TrackList>* in);



};
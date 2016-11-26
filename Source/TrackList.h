#pragma once
//This is a symbolic global variable, it's a value that will be constant and so wont take up ram. Also remember to update it if you add something to the metadata array
#define METADATA_SIZE 5
#include <string>
using std::string;


class Track
{
	//this is an array of the actual metadata
	string* metadataArr_ = nullptr;
	//Used to identify tracks while indexed
	int trackID_;
	//this is an array of labels for every metadata entry, it is static and constant and don't touch it. I only barely understand why it is the way it is.
	//It is initialized in the cpp but declared in the header
	static const string metadataLabelArr_[METADATA_SIZE];

public:
	Track() { /* literally nothing  */ }
	Track(string newMetadataArr[METADATA_SIZE]);

	string getMetadata(string metadataLabel);
	void setMetadata(string metadataLabel, string newData);
	
	int getTrackID() { return trackID_; }
	void setTrackID(int trackID) { trackID_ = trackID; }

	int indexOfThisMetadata(string metadataLabel);
	string labelOfThisIndex(int index);
	int metadataSize() { return METADATA_SIZE; }

};

//A structure is a class with default public fields. It is used for classes that would only hold data without having any functions
struct Node
{
	//Each node holds a track pointer and a node pointer
	Track* data;
	Node* next;

	Node(Track* newData);
	Node(Track* newData, Node* nextNode);

};

class TrackList
{
	Node* first_;
	Node* last_;

	string name_;

	int size_;

public:
	TrackList(string newName);
	TrackList(string newName, Track* newTrack);

	void AddTrack(Track* newTrack);
	void AddTrack(Track* newTrack, int index);
	void RemoveTrack(int index);
	Track* GetTrack(int index);
	int Size() { return size_; }
};
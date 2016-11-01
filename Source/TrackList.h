#pragma once
//This is a symbolic global variable, it's a value that will be constant and so wont take up ram. Also remember to update it if you add something to the metadata array
#define METADATA_SIZE 5
#include <string>
using std::string;


//A structure is a class with default public fields. It is used for classes that would only hold data without having any functions
struct Node
{
	//Each node holds a void pointer and two node pointers, this allows navigation backward in the list, which makes it esier to navigate a playlist
	void* data;
	Node* previous;
	Node* next;

	Node(void* newData, Node* previousNode, Node* nextNode);

};

class Track
{
	//this is an array of the actual metadata, it is instantiated as an array of null pointers
	void** metadataArr = nullptr;
	//this is an array of labels for every metadata entry
	const string metadataLabelArr[METADATA_SIZE] =
	{ "id", "address", "title", "artist", "year" };

public:
	Track() { /* literally nothing  */ }
	Track(void* newMetadataArr[METADATA_SIZE]);
	void* getMetadata(string metadataLabel);
	void setMetadata(string metadataLabel, void* newData);
	int indexOfThisMetadata(string metadataLabel);			//This function will hold the code to search metadata
};

class TrackList
{
	Node* first_;
	Node* last_;
	Node* current_;

	int currentIndex_;
	int size_;

public:
	TrackList();
	TrackList(Track* newTrack);
};
#include "TrackList.h"

Node::Node(void* newData, Node* previousNode, Node* nextNode)
{
	this->data = newData;
	this->previous = previousNode;
	this->next = nextNode;
}




Track::Track(void* newMetadataArr[METADATA_SIZE])
{
	metadataArr = newMetadataArr;
}

void* Track::getMetadata(string metadataLabel)
{
	return metadataArr[indexOfThisMetadata(metadataLabel)];
}

void Track::setMetadata(string metadataLabel, void* data)
{
	metadataArr[indexOfThisMetadata(metadataLabel)] = data;
}

//This will take in a string and return the index of said metadata in the metadataArr
int Track::indexOfThisMetadata(string metadataLabel)
{
	//iterate through metadataTypeArr
	for (int i = 0; i <= METADATA_SIZE; i++)
	{
		if (metadataLabel.compare(metadataLabelArr[i]))
			return i;
	}
	
	return -1; //return -1 so that if the function fails it can be easily identified
}





TrackList::TrackList(Track* newTrack)
{
	
}

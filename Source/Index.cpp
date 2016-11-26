#include "Index.h"

Index::Index()
{
	trackIndexLocation_ = "trackIndex.txt";
	tracklistIndexLocation_ = "trackListIndex.txt";
	lastID_ = 0;

	initiateIndexFromConfig();
}

void Index::initiateIndexFromConfig()
{
	ifstream config(CONFIG_FILE);
	string currentLine = NULL;

	if (!config.good)
		return;

	//define the easy ones
	getline(config, trackIndexLocation_);
	getline(config, tracklistIndexLocation_);
	string strLastID = NULL;
	getline(config, strLastID);
	lastID_ = stoi(strLastID);

	bool isDirectory = false;
	bool isUnusedID = false;

	//define the vectors
	while (getline(config, currentLine))
	{
		if (isDirectory)
			directories_.push_back(currentLine);
		else if (isUnusedID)
			unusedID_.push_back(stoi(currentLine));

		else if (currentLine.compare("directories_") == 0)
			isDirectory = true;
		else if (currentLine.compare("/directories_") == 0)
			isDirectory = false;

		else if (currentLine.compare("unusedID_") == 0)
			isUnusedID = true;
		else if (currentLine.compare("/unusedID_") == 0)
			isUnusedID = false;
	}
}

void Index::writeFieldsToConfig()
{
	remove(CONFIG_FILE);
	ofstream config(CONFIG_FILE);

	config << trackIndexLocation_ << endl;
	config << tracklistIndexLocation_ << endl;
	config << lastID_ << endl;

	//write out directories
	config << "directories_" << endl;
	for (string &directory : directories_)
	{
		config << directory << endl;
	}
	config << "/directories_" << endl;

	//write out unused IDs
	config << "unusedID_" << endl;
	for (int &iD : unusedID_)
	{
		config << iD << endl;
	}
	config << "/unusedID_" << endl;

}

void Index::RemoveDirectory(string rmDirectory)
{
	for (int i = 0; i < directories_.size; i++)
	{
		if (directories_[i].compare(rmDirectory) == 0)
		{
			directories_.erase[i];
		}
	}
}

vector<TrackList> Index::ReadTrackListIndex()
{
	vector<TrackList> currentList;
	vector<int> iDList;

	ifstream trackListIndexFile(tracklistIndexLocation_.c_str());

	string currentLine = NULL;
	bool isTrackID = false;

	//Run as long as there is another line
	while (getline(trackListIndexFile, currentLine))
	{
		//If the line is flagged as a track ID, add it to the id list
		if (isTrackID)
		{
			iDList.push_back(stoi(currentLine));
		}
		//If the line is a match, flag all following lines as track IDs and add them to a fresh vector
		else if (currentLine.compare("TrackList") == 0)
		{
			isTrackID = true;
			iDList.clear();
		}
		//If the line is a match, stop flagging all lines as track IDs, use the collected Ids to make a TrackList
		else if (currentLine.compare("/TrackList") == 0)
		{
			isTrackID = false;
			currentList.push_back(TrackListFromIDList(iDList));
		}
	}

	return currentList;
}

void Index::WriteTrackListIndex(vector<TrackList> tListV)
{
	remove(tracklistIndexLocation_.c_str());
	ofstream trackListIndexFile(tracklistIndexLocation_.c_str());

	Track* currentTrack = nullptr;

	for (TrackList &currentList : tListV)
	{
		trackListIndexFile << "TrackList" << endl << currentList.name << endl;

		for (int i = 0; i < currentList.Size; i++)
		{
			currentTrack = currentList.GetTrack(i);
			trackListIndexFile << currentTrack->getTrackID << endl;
		}

		trackListIndexFile << "/TrackList";
	}
}

void Index::UpdateTrackIndex()
{
	ifstream inDex(trackIndexLocation_);
	
	if (!inDex.good)
	{
		WriteTrackIndex();
		return;
	}
}

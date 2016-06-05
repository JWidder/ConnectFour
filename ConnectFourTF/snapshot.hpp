#pragma once
#include <vector>

namespace std
{
	enum searchDirection {vertical, links, rechts};

	class snapshot
	{
	private:
		int xLen;
		int yLen;
		int modul;
		int status;
		int _player;
		vector<int> snapshotBoard;
		vector<int> snapshotOutput;
		vector<int> snapshotVertical;
		vector<int> snapshotLeft;
		vector<int> snapshotRight;

		int calculatePosition(int row,int column);
	public:
		snapshot(int xLen,int yLen);
		snapshot(const snapshot & snapshot);
		void addButton(int column, int player);
		vector<int>getBoardOutput();
		vector<int>getBoardInput();
		void setModule(int button);
		void setStatus(int inStatus);
		void setPlayer(int player);
		int getPlayer();
		vector<int> *getBoardData();
		vector<int> *getModulData();
		double checkDirection(searchDirection direction, int player, int column, int row);
	};
}
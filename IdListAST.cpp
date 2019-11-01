#include "IdListAST.h"


IdListAST::IdListAST()
{
	this->idItemASTs = new vector<IdItemAST*>();
}

IdListAST::IdListAST(IdItemAST* item)
{
	this->idItemASTs = new vector<IdItemAST*>();
	addIdItem(item);
}

IdListAST::~IdListAST()
{
	for (int i = 0; i < idItemASTs->size(); i++)
	{
		delete idItemASTs->at(i);
	}
	delete idItemASTs;
}

void IdListAST::addIdItem(IdItemAST* item)
{
	this->idItemASTs->push_back(item);
}

map<string, ID*> IdListAST::codegenMap()
{
	map<string, ID*> IdListMap;
	pair<string, ID*> IdItemPair;
	cout << "IdListAST" << "\n";
	for (int i = idItemASTs->size() - 1; i >= 0; i--)
	{
		IdItemPair = idItemASTs->at(i)->codegenPair();
		IdListMap.insert(IdItemPair);
		//if (!idItemASTs->at(i)->decVarNameAST->LSRS) {//��������
		//	IdItemPair = idItemASTs->at(i)->codegenPair();
		//	IdListMap.insert(IdItemPair);
		//}
		//else {//������
		//	IdVecItem = idItemASTs->at(i)->codegenPair();
		//	ArrayListMap.insert(IdVecItem);
		//}
	}
	return IdListMap;
}
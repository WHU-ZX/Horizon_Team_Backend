#include "IdItemAST.h"

IdItemAST::IdItemAST(DecVarNameAST* decVarNameAST)
{
	this->decVarNameAST = decVarNameAST;
}

IdItemAST::IdItemAST(DecVarNameAST* decVarNameAST, ExpAST* exp)
{
	this->decVarNameAST = decVarNameAST;
	this->exp = exp;
}

IdItemAST::IdItemAST(DecVarNameAST* decVarNameAST, ExpListAST* exps)
{
	this->decVarNameAST = decVarNameAST;
	this->exps = exps;
}

IdItemAST::~IdItemAST()
{
	delete this->decVarNameAST;
	if (this->exp != nullptr)
	{
		delete this->exp;
	}
	if (this->exps != nullptr)
	{
		delete this->exps;
	}
}

string IdItemAST::codegenStr()
{
	return string();
}

vector<string> IdItemAST::codegenStrVec()
{
	return vector<string>();
}

//map<string, Value*>* IdItemAST::codegenMap()
//{
//	return nullptr;
//}

pair<string, ID*> IdItemAST::codegenPair() {//��������
	pair<string, ID*> pair;
	pair.first = decVarNameAST->codegenStr();
	if (!decVarNameAST->LSRS) {//�����������
		if (exp != NULL) {
			vector<Value*> valVector;
			valVector.push_back(exp->codegen());
			ID* id = new ID(false, valVector);
			pair.second = id;
			return pair;
		}
		else {//δ����ֵ

		}
	}
	else {//������
		vector<Value*> valVector;
		ID* id = new ID(true);
		if (decVarNameAST->intAST == nullptr) {//���û����ʽָ������
			if (this->exps != nullptr) {
				for (int i = this->exps->exps->size() - 1; i >= 0; i--) {
					ExpAST* exp = this->exps->exps->at(i);
					valVector.push_back(exp->codegen());
					
				}
				id->elementNum = this->exps->exps->size();
			}
			else {
				throw Exception(OtherEx, 0, "IdItemAST::codegenPairVec() ���ô���!");
			}
		}
		else {//��ʽָ���˳���
			int arrayLength = decVarNameAST->intAST->integer;//���鳤��
			id->elementNum = arrayLength;
			if (this->exps != nullptr) {//������˳�ֵ ���û�����Ĳ���
				for (int i = this->exps->exps->size() - 1; i >= 0; i--) {
					ExpAST* exp = this->exps->exps->at(i);
					valVector.push_back(exp->codegen());
				}
				int rest = arrayLength - this->exps->exps->size();
				if (this->exps->expType == zx::Type::INT) {
					for (int i = 0; i < rest; i++) {
						valVector.push_back(ConstantInt::get(TheContext, APInt(32, 0)));
					}
				}
				else if (this->exps->expType == zx::Type::REAL) {
					for (int i = 0; i < rest; i++) {
						valVector.push_back(ConstantFP::get(TheContext, APFloat(0.0)));
					}
				}
				else if (this->exps->expType == zx::Type::STRING) {//�д����

				}
				else if (this->exps->expType == zx::Type::POINTER) {//�д����

				}
				else if (this->exps->expType == zx::Type::STRUCT) {//�д����

				}
				else if (this->exps->expType == zx::Type::CHAR) {//�д����
					/*for (int i = 0; i < rest; i++) {
						valVector.push_back(ConstantFP::get(TheContext, AP);
					}*/
				}
			}
			else {//���û�и���ֵ   ȫ���Լ�����ֵ

			}

		}
		id->valueVector = valVector;
		return pair;
	}
}

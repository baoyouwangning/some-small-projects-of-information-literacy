#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//Ԫ��λ��
class Location
{
public:
	Location(int aRow = 0, int aCol = 0, int aLength = 0, Location *aNext = NULL);
	~Location();

	void setRow(int aRow);
	void setCol(int aCol);
	void setLength(int aLength);
	void setNext(Location * aNext);

	int getRow() const;
	int getCol() const;
	int getLength() const;
	Location * getNext() const;

	void display() const;
private:
	int m_row; //�ڼ���
	int m_col; //�ڼ�����
	int m_length; //����
	Location *m_next;	//�¸�λ��
};

//������ֵ��(������Ԫ��)
class Seed
{
public:
	Seed(char * aKey = "blcakpop", int aFrenqucy = 1, Location * aLocation = NULL, Seed * aNext = NULL);
	~Seed();

	void setKey(char * aKey);
	void setFrequency(int aFrequency);
	void setLocationList(Location * aLocationList);
	void setNext(Seed * aNext);

	char * getKey() const;
	int getFrequency() const;
	Location * getLocationList() const;
	Seed * getNext() const;

	void display() const;
private:
	char * m_key;
	int m_frequency;
	Location * m_locationList;
	Seed * m_next;
};

class Section
{
public:
	Section(int aMark = 0, char * aContent = "Hello!I'm Wang Ning!", Section * aNext = NULL);
	~Section();

	void setMark(int aMark);
	void setContent(char * aContent);
	void setNext(Section * aNext);

	int getMark() const;
	char * getContent() const;
	Section * getNext() const;

	void display() const;
private:
	int m_mark;
	char * m_content;
	Section * m_next;
};

//����������
class essayReptiles
{
public:
	essayReptiles(char * aDate = "2014-1-1", char * aTitle = "Hello world", char * anEssay = "Hello world! ^_^");
	~essayReptiles();
	
	void setDate( char *aDate);
	void setTitle( char *aTitle);
	void setEssay( char *anEssay);
	
	char * getDate() const;
	char * getTitle() const;
	char * getEssay() const;
	char * getUnique() const;

	Section * getSectionLists() const;
	int getSectionSize() const;
	Seed * getSeedLists() const;
	int getSeedSize() const;

	void displayDate() const;
	void displayTitle() const;
	void displayEssay() const;  //��ʾȫ��
	void displayUnique() const;  //��ʾ�ҵ����У�Ƶ����ߵļ�ֵ��
	void displaySectionLists() const; //��ʾ�ֶκ�Ķ���
	void displaySeedLists() const;	//��ʾ��ֵ�б�

	bool Search(char * aStr) const;
private:
	//������Ϣ
	char * m_date;  //�ҵ�ʱ��
	char * m_title;  //�ҵı���
	char * m_essay;  //�ҵ�����
	char * m_unique; //�ҵ�����(Ƶ����ߵ�ֵ)

	//���ķֶ�����
	Section * m_sectionList; //�ҵķֶ�����
	int m_sectionSize; //�ҵĶ���
	
	//��ֵ�б�2
	Seed * m_seedList; //��ֵ�б��׵�ַ
	int m_seedSize;	//��ֵ����
};

#endif  // #ifndef INVERTEDINDEX_H

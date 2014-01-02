#include <ctype.h>
#include "InvertedIndex.h"
#include "JR_Color.h"

//Ԫ��λ����
Location::Location(int aRow, int aCol, int aLength, Location *aNext)
{
	m_row = aRow;
	m_col = aCol;
	m_length = aLength;
	m_next = aNext;
}
Location::~Location()
{
	//if( m_next )
	//{
	//	delete m_next; //bug
	//}
	//cout << "delete" << endl;

	delete m_next;
}
void Location::setRow(int aRow)
{
	m_row = aRow;
}
void Location::setCol(int aCol)
{
	m_col = aCol;
}
void Location::setLength(int aLength)
{
	m_length = aLength;
}
void Location::setNext(Location * aNext)
{
	m_next = aNext;
}
int Location::getRow() const
{
	return m_row;
}
int Location::getCol() const
{
	return m_col;
}
int Location::getLength() const
{
	return m_length;
}
Location * Location::getNext() const
{
	return m_next;
}
void Location::display() const
{
	if( m_next )				//�ݹ����locationList�����Կ�����Ҳ�ǵ���λ���б�
	{
		m_next ->display();
	}

	cout << '(' << m_row << ',' << m_col << ',' << m_length << ") ";
}



//������ֵ��(������Ԫ��)
Seed::Seed(char * aKey, int aFrequency, Location * aLocation, Seed * aNext)
{
	m_key = new char[strlen(aKey)+1];
	strcpy(m_key,aKey);

	m_frequency = aFrequency;

	m_locationList = aLocation;
	
	m_next = aNext;
}
Seed::~Seed()
{	
	//if( m_next )
	//{
	//	delete m_next;  //bug
	//}

	delete []m_key;
	delete m_locationList;
}
void Seed::setKey(char * aKey)
{	
	m_key = new char[strlen(aKey) + 1];
	strcpy(m_key,aKey);
}
void Seed::setFrequency(int aFrequency)
{
	m_frequency = aFrequency;
}
void Seed::setLocationList(Location * aLocationList)
{
	m_locationList = aLocationList;
}
void Seed::setNext(Seed * aNext)
{
	m_next = aNext;
}
char * Seed::getKey() const
{
	return m_key;
}
int Seed::getFrequency() const
{
	return m_frequency;
}
Location * Seed::getLocationList() const
{
	return m_locationList;
}
Seed * Seed::getNext() const
{
	return m_next;
}
void Seed::display() const
{
	if( m_next )   //�ݹ������ʾseed�б����Կ�����seelistsΪ������ʾ��
	{
		m_next ->display();   
	}

	cout << m_key << ' '; //keyֵ

	cout << m_frequency << "times ";

	m_locationList ->display(); //keyֵ����λ�õ��б�(Ҳ��ݹ�)
	
	cout << endl;
}

//��������
Section::Section(int aMark, char * aContent, Section * aNext)
{
	m_mark = aMark;
	
	m_content = new char[strlen(aContent) + 1];
	strcpy(m_content,aContent);

	m_next = aNext;
}
Section::~Section()
{
	if( m_next )
	{
		m_next;  
	}

	delete m_next;
}
void Section::setMark(int aMark)
{
	m_mark = aMark;
}
void Section::setContent(char * aContent)
{
	m_content = new char[strlen(aContent) + 1];
	strcpy(m_content,aContent);
}
void Section::setNext(Section * aNext)
{
	m_next = aNext;
}
int Section::getMark() const
{
	return m_mark;
}
char * Section::getContent() const
{
	return m_content;
}
Section * Section::getNext() const
{
	return m_next;
}
void Section::display() const
{
	if( m_next )
	{
		m_next ->display();
	}
	cout << m_mark << ":" << m_content << endl;
}

//����������
essayReptiles::essayReptiles(char * aDate, char * aTitle, char * anEssay)
{
	m_date = new char[strlen(aDate)+1];
	strcpy(m_date,aDate);

	m_title = new char[strlen(aTitle)+1];
	strcpy(m_title,aTitle);

	m_essay = new char[strlen(anEssay)+1];
	strcpy(m_essay,anEssay);

	m_unique = NULL;

	m_sectionList = NULL;
	m_sectionSize = 0; //�ҵĶ���
	m_seedList = NULL;
	m_seedSize = 0;	//��ֵ����

	int wordIndex = 0;
	int wordCount = 0;     //��ƪ���ĵ�ǰ����λ��
	int tempWordCount = 0; // ���ʵ�����ĸλ�� ��ֵ�� wordCount ��  
	int sectionWordCount = 0; //��ǰ�εĵ��ʵ�λ��

	int sectionCount = 0;  //�������
	char * tempWord = NULL;
	Seed ** seed_p = &m_seedList;
	Seed * temp_seed_p = NULL;
	Location *location_p = NULL;

	Seed * temp_seed = NULL;
	Location * temp_location = NULL;

	char * tempSection = NULL;
	Section * temp_section_p = m_sectionList; //���б�����Ҫÿ�α����Ƿ������ظ���

	//Ƶ����¼
	Seed * m_frequency_temp = NULL;
	int frequencyFlag = 0;

	for(int i = 0; i < strlen(m_essay); i++, sectionWordCount++)   //ɨ��ȫ�ģ�һ�α����������ж���
	{	
		//ɨ�赽һ����
		//if( m_essay[i] == ' ' || m_essay[i] == ',' || m_essay[i] == '.' || m_essay[i] == '\\' || m_essay[i] == '(' || m_essay[i] == ')' )
		if( !isalpha(m_essay[i]) ) 
		{	
			tempWordCount = wordCount;  //�洢��ǰ���ʵ�����ĸλ��
			tempWord = new char[i - tempWordCount + 1];  //�洢ƴ�ӵ���

			for(wordIndex = 0; wordIndex < (i - tempWordCount); wordIndex++)  //д��tempWord����
			{
				tempWord[wordIndex] = m_essay[wordCount++];
			}
			tempWord[wordIndex] = '\0';

			//cout << tempWord << endl;
			
			//��ʱ wordCount == i �²� wordCount ָ���¸����ʵ�����ĸ
			wordCount = i + 1;

			temp_location = new Location(sectionCount,sectionWordCount - ( i - tempWordCount),i - tempWordCount,NULL);//�洢��ǰ���ʵ�λ��
			temp_seed = new Seed(tempWord,1,temp_location,NULL);

			/*cout << temp_location ->getRow() << endl;
			cout << temp_location ->getCol() << endl;*/

			/*cout << temp_seed ->getKey() << endl;
			cout << temp_seed ->getLocationList() << endl;
			cout << temp_seed ->getNext() << endl;*/

			//ɨ�����м�ֵ����
			temp_seed_p = m_seedList;
			while( temp_seed_p && (strcmp(temp_seed_p ->getKey(),tempWord)) && (temp_seed_p ->getNext()) )  //�ҵ���ǰֵ�Ƿ�����λ���б�
			{
				temp_seed_p = temp_seed_p ->getNext();
			}
			seed_p = &temp_seed_p;
			
			if( !(*seed_p) ) //����һ��temp_seed == NULLʱ
			{
				m_seedList = temp_seed;  // �ѵ�ǰ��ֵ�ĵ�ַ����seedList
				m_seedSize++;         //��ֵ++
			}
			else if( !(strcmp((*seed_p) ->getKey(),tempWord)) )  //�鵽�ؼ�ֵ
			{	
				(*seed_p) ->setFrequency((*seed_p) ->getFrequency() + 1);  //seedƵ����һ

				if( (*seed_p) ->getFrequency() > frequencyFlag )  //�����ǰ��ֵƵ������ frequencyFlag
				{
					frequencyFlag = (*seed_p) ->getFrequency();  //���� frequencyFlag
					
					//���¼�ֵ
					delete []m_unique;
					m_unique = new char[strlen((*seed_p) ->getKey()) + 1]; 
					strcpy(m_unique,(*seed_p) ->getKey());
				}
				
				location_p = (*seed_p) ->getLocationList();

				while( location_p ->getNext() )    //�ҵ��ü�ֵλ���б������λ��
				{
					location_p = location_p ->getNext();
				}
				location_p ->setNext(temp_location);
			}
			else		//���޸ü�ֵ�ļ�¼ʱ
			{
				(*seed_p) ->setNext(temp_seed);         //�ڼ�ֵ�б��������¼�ֵ
				m_seedSize++;                 //��ֵ++
			}
		}

		//ɨ�赽һ��   //һ�����ǵ��ж�
		if( m_essay[i] == '.' || m_essay[i] == '!' || m_essay[i] == ';' || m_essay[i] == '?' )   
		{
			tempSection = new char[sectionWordCount + 2];

			for(wordIndex = 0; wordIndex < sectionWordCount + 1; wordIndex++)
			{
				tempSection[wordIndex] = m_essay[i - sectionWordCount + wordIndex];
			}
			//tempSection[wordIndex] = m_essay[i];
			tempSection[wordIndex+1] = '\0';

			if( !temp_section_p )   //��һ��
			{
				m_sectionList = new Section(sectionCount,tempSection,NULL);
				temp_section_p = m_sectionList;
			}
			else
			{
				temp_section_p ->setNext(new Section(sectionCount,tempSection,NULL));
				temp_section_p = temp_section_p ->getNext();
			}

			m_sectionSize++;
			sectionWordCount = 0;   //�����ַ�����������
			sectionCount++;        //��������һ
			i++;
		}
	}	
}
essayReptiles::~essayReptiles()
{
	//������Ϣ
	delete m_date;  //�ҵ�ʱ��
	delete m_title;  //�ҵı���
	delete m_essay;  //�ҵ�����
	delete m_unique; //�ҵ�����(Ƶ����ߵ�ֵ)

	//�����б�
	delete m_sectionList;

	//��ֵ�б�
	delete m_seedList; //��ֵ����
}
void essayReptiles::setDate( char *aDate)
{
	m_date = aDate;
}
void essayReptiles::setTitle( char *aTitle)
{
	m_title = aTitle;
}
void essayReptiles::setEssay( char *anEssay)
{
	m_essay = anEssay;
}
char * essayReptiles::getDate() const
{
	return m_date;
}
char * essayReptiles::getTitle() const
{
	return m_title;
}
char * essayReptiles::getEssay() const
{
	return m_essay;
}
char * essayReptiles::getUnique() const
{
	return m_unique;
}
Section * essayReptiles::getSectionLists() const
{
	return m_sectionList;
}
int essayReptiles::getSectionSize() const
{
	return m_sectionSize;
}
Seed * essayReptiles::getSeedLists() const
{
	return m_seedList;
}
int essayReptiles::getSeedSize() const
{
	return m_seedSize;
}
void essayReptiles::displayDate() const
{
	cout << "=================================================" << endl;
	cout << "Date:";
	cout << ' ' << m_date << ' ' << endl;
}
void essayReptiles::displayTitle() const
{
	cout << "=================================================" << endl;
	cout << "Title:";
	cout << ' ' << m_title << ' ' << endl;
}
void essayReptiles::displayEssay() const
{
	cout << "=================================================" << endl;
	cout << "Detail:" << endl;
	cout << m_essay << endl;
}
void essayReptiles::displayUnique() const
{
	cout << "=================================================" << endl;
	cout << "My unique: " << endl;
	cout << m_unique << endl;
}
void essayReptiles::displaySectionLists() const
{	
	cout << "=================================================" << endl;
	cout << "In section detail:" << endl;
	m_sectionList ->display();
}
void essayReptiles::displaySeedLists() const
{	
	cout << "=================================================" << endl;
	cout << "In keywords detail: ";
	cout << " +This text have " << m_seedSize << " keywords+" << endl; 
	
	m_seedList ->display();
}

bool essayReptiles::Search(char * aStr) const
{

	cout << "=================================================" << endl;
	char * search_key = new char[strlen(aStr) + 1];
	strcpy(search_key,aStr);

	Seed * temp_seed_p = m_seedList;
	Location * temp_location_p = NULL;

	Section * temp_section_p = m_sectionList;

	char * temp_conten_p = NULL;

	while( temp_seed_p && strcmp(temp_seed_p ->getKey(),search_key) && temp_seed_p ->getNext() )
	{
		temp_seed_p = temp_seed_p ->getNext();
	}

	if( !strcmp(temp_seed_p ->getKey(),search_key) )   //�ҵ��ü�ֵ
	{	
		cout << "Find it! ^_^" << endl;
		cout << "< " << temp_seed_p ->getKey() << " >" << " appears " << temp_seed_p ->getFrequency() << " times in this text!" << endl;
		cout << "Hey! Here: " << endl;
		
		temp_location_p = temp_seed_p ->getLocationList();  //��õ�ǰ��ֵ��λ������

		while( temp_location_p )   //���α����ü�ֵ��λ������
		{
			 //���ü�ֵ��λ����ͬ�����ж��λ�ó���ʱ,
			if( temp_location_p ->getNext() && temp_location_p ->getRow() == temp_location_p ->getNext() ->getRow() )  
			{
				cout << '(' << temp_location_p ->getRow() << ',' << temp_location_p ->getCol() << ") ";
				temp_location_p = temp_location_p ->getNext();

				continue;
			}

			temp_section_p = m_sectionList;
			while( temp_section_p )   //���α����ö��б�
			{
				if( temp_section_p ->getMark() == temp_location_p ->getRow() )   //���öε� mark ==  �ü�ֵ�����ڵĶ�ʱ
				{
					cout << '(' << temp_location_p ->getRow() << ',' << temp_location_p ->getCol() << ") ";

					//to do something here to let you keywords change background in this section!
					temp_conten_p = new char[strlen(temp_section_p ->getContent()) + 1];
					strcpy(temp_conten_p,temp_section_p ->getContent());

					for(int iCol = 0; temp_conten_p[iCol] != '\0'; iCol++)  //�����ö�����
					{
						if( iCol == temp_location_p ->getCol() )  //���ö��ߵ��ü�ֵ��λ��ʱ
						{	
							JR_SetColor(12,10);   //change your words color!  //
							for(int iLocation = 0; iLocation < temp_location_p ->getLength(); iLocation++, iCol++)  //����õ���
							{
								cout << temp_section_p ->getContent()[iCol];
							}
						}

						JR_SetColor(7,0);
						cout << temp_section_p ->getContent()[iCol];  //�öεķǹؼ��ֲ���
					}

					cout << endl;
				}

				temp_section_p = temp_section_p ->getNext();
			}

			temp_location_p = temp_location_p ->getNext();
		}
		cout << endl;

		return true;  
	}  //����

	cout << "Sorry! I can't find it! -_-|||" << endl;
	return false;
}



#include "Chinese.h"
string ChineseWord(const char* wordId)
{
	static ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("ChineseWords.xml");
	auto txt_map = txt_vec.at(0).asValueMap();
	string ret = txt_map.at(wordId).asString();
	return ret;
}

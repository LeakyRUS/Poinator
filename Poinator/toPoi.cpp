#include "topoi.h"

static const std::string libStrings[] = //0-63
{
	// =
	"Poi!!",

	// 3 bit group + !
	// 0-7
	"poi!",//0
	"Poi!",//1
	"pOi!",//2
	"POi!",//3
	"poI!",//4
	"PoI!",//5
	"pOI!",//6
	"POI!",//7

	// 3 bit group
	// 8-16
	"poi",//0	8
	"Poi",//1	9
	"pOi",//2	10
	"POi",//3	11
	"poI",//4	12
	"PoI",//5	13
	"pOI",//6	14
	"POI",//7	15

	// 4 bitGroup
	// 17-32
	"pooi",//0	16
	"Pooi",//1	17
	"pOoi",//2	18
	"POoi",//3	19
	"poOi",//4	20
	"PoOi",//5	21
	"pOOi",//6	22
	"POOi",//7	23
	"pooI",//8	24
	"PooI",//9	25
	"pOoI",//10	26
	"POoI",//11	27
	"poOI",//12	28
	"PoOI",//13	29
	"pOOI",//14	30
	"POOI",//15	31

	// 5 bitGrout
	// 24-56
	"poooi",//0		32
	"Poooi",//1		33
	"pOooi",//2		34
	"POooi",//3		35
	"poOoi",//4		36
	"PoOoi",//5		37
	"pOOoi",//6		38
	"POOoi",//7		39
	"pooOi",//8		40
	"PooOi",//9		41
	"pOoOi",//10	42
	"POoOi",//11	43
	"poOOi",//12	44
	"PoOOi",//13	45
	"pOOOi",//14	46
	"POOOi",//15	47	
	"poooI",//16	48
	"PoooI",//17	49
	"pOooI",//18	50
	"POooI",//19	51
	"poOoI",//20	52
	"PoOoI",//21	53
	"pOOoI",//22	54
	"POOoI",//23	55
	"pooOI",//24	56
	"PooOI",//25	57
	"pOoOI",//26	58
	"POoOI",//27	59
	"poOOI",//28	60
	"PoOOI",//29	61
	"pOOOI",//30	62
	"POOOI" //31	63

};

static const std::string base64_chars = "=ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string toPoi(std::string base64Code)
{
	std::string exitPoiString;
	while(base64Code != "")
	{
		for (int i = 0; i < 65; i++)
		{
			if (base64Code[0] == base64_chars[i])
			{
				exitPoiString += libStrings[i] + ' ';
				base64Code.erase(0, 1);
				break;
			}
		}
	}
	return exitPoiString;
}

std::string fromPoi(std::string poiText)
{
	std::string base64Exit;

	poiText.erase(std::remove(poiText.begin(), poiText.end(), ' '), poiText.end());

	while (poiText != "")
	{
		bool isErr = true;
		for (int i = 0; i < 65; i++)
		{
			auto size = libStrings[i].size();
			std::string test = poiText.substr(0, size);
			if (test == libStrings[i])
			{
				base64Exit += base64_chars[i];
				poiText.erase(0, size);
				isErr = false;
				break;
			}
		}
		if (isErr) 
			throw std::runtime_error("Decoding error - wrong poi text!");
	}

	return base64Exit;
}
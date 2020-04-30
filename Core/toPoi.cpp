#include "topoi.h"
#include <algorithm>
#include <stdexcept>

static const std::vector<std::string> poiStrings = //256
{
	//256
	"poooi!!",
	"Poooi!!",
	"pOooi!!",
	"POooi!!",
	"poOoi!!",
	"PoOoi!!",
	"pOOoi!!",
	"POOoi!!",
	"pooOi!!",
	"PooOi!!",
	"pOoOi!!",
	"POoOi!!",
	"poOOi!!",
	"PoOOi!!",
	"pOOOi!!",
	"POOOi!!",

	//240
	"poooi!?",
	"Poooi!?",
	"pOooi!?",
	"POooi!?",
	"poOoi!?",
	"PoOoi!?",
	"pOOoi!?",
	"POOoi!?",
	"pooOi!?",
	"PooOi!?",
	"pOoOi!?",
	"POoOi!?",
	"poOOi!?",
	"PoOOi!?",
	"pOOOi!?",
	"POOOi!?",
	"poooI!?",
	"PoooI!?",
	"pOooI!?",
	"POooI!?",
	"poOoI!?",
	"PoOoI!?",
	"pOOoI!?",
	"POOoI!?",
	"pooOI!?",
	"PooOI!?",
	"pOoOI!?",
	"POoOI!?",
	"poOOI!?",
	"PoOOI!?",
	"pOOOI!?",
	"POOOI!?",

	//208
	"poooi!",
	"Poooi!",
	"pOooi!",
	"POooi!",
	"poOoi!",
	"PoOoi!",
	"pOOoi!",
	"POOoi!",
	"pooOi!",
	"PooOi!",
	"pOoOi!",
	"POoOi!",
	"poOOi!",
	"PoOOi!",
	"pOOOi!",
	"POOOi!",
	"poooI!",
	"PoooI!",
	"pOooI!",
	"POooI!",
	"poOoI!",
	"PoOoI!",
	"pOOoI!",
	"POOoI!",
	"pooOI!",
	"PooOI!",
	"pOoOI!",
	"POoOI!",
	"poOOI!",
	"PoOOI!",
	"pOOOI!",
	"POOOI!",

	//176
	"poooi",
	"Poooi",
	"pOooi",
	"POooi",
	"poOoi",
	"PoOoi",
	"pOOoi",
	"POOoi",
	"pooOi",
	"PooOi",
	"pOoOi",
	"POoOi",
	"poOOi",
	"PoOOi",
	"pOOOi",
	"POOOi",
	"poooI",
	"PoooI",
	"pOooI",
	"POooI",
	"poOoI",
	"PoOoI",
	"pOOoI",
	"POOoI",
	"pooOI",
	"PooOI",
	"pOoOI",
	"POoOI",
	"poOOI",
	"PoOOI",
	"pOOOI",
	"POOOI",

	//144
	"pooi!!!",
	"Pooi!!!",
	"pOoi!!!",
	"POoi!!!",
	"poOi!!!",
	"PoOi!!!",
	"pOOi!!!",
	"POOi!!!",
	"pooI!!!",
	"PooI!!!",
	"pOoI!!!",
	"POoI!!!",
	"poOI!!!",
	"PoOI!!!",
	"pOOI!!!",
	"POOI!!!",

	//128
	"pooi!?",
	"Pooi!?",
	"pOoi!?",
	"POoi!?",
	"poOi!?",
	"PoOi!?",
	"pOOi!?",
	"POOi!?",
	"pooI!?",
	"PooI!?",
	"pOoI!?",
	"POoI!?",
	"poOI!?",
	"PoOI!?",
	"pOOI!?",
	"POOI!?",

	//112
	"pooi!!",
	"Pooi!!",
	"pOoi!!",
	"POoi!!",
	"poOi!!",
	"PoOi!!",
	"pOOi!!",
	"POOi!!",
	"pooI!!",
	"PooI!!",
	"pOoI!!",
	"POoI!!",
	"poOI!!",
	"PoOI!!",
	"pOOI!!",
	"POOI!!",

	//96
	"pooi?",
	"Pooi?",
	"pOoi?",
	"POoi?",
	"poOi?",
	"PoOi?",
	"pOOi?",
	"POOi?",
	"pooI?",
	"PooI?",
	"pOoI?",
	"POoI?",
	"poOI?",
	"PoOI?",
	"pOOI?",
	"POOI?",

	//80
	"pooi!",
	"Pooi!",
	"pOoi!",
	"POoi!",
	"poOi!",
	"PoOi!",
	"pOOi!",
	"POOi!",
	"pooI!",
	"PooI!",
	"pOoI!",
	"POoI!",
	"poOI!",
	"PoOI!",
	"pOOI!",
	"POOI!",

	//64
	"pooi",
	"Pooi",
	"pOoi",
	"POoi",
	"poOi",
	"PoOi",
	"pOOi",
	"POOi",
	"pooI",
	"PooI",
	"pOoI",
	"POoI",
	"poOI",
	"PoOI",
	"pOOI",
	"POOI",

	//48
	"poi!!!",
	"Poi!!!",
	"pOi!!!",
	"POi!!!",
	"poI!!!",
	"PoI!!!",
	"pOI!!!",
	"POI!!!",

	//40
	"poi!!",
	"Poi!!",
	"pOi!!",
	"POi!!",
	"poI!!",
	"PoI!!",
	"pOI!!",
	"POI!!",

	//32
	"poi!?",
	"Poi!?",
	"pOi!?",
	"POi!?",
	"poI!?",
	"PoI!?",
	"pOI!?",
	"POI!?",

	//24
	"poi!",
	"Poi!",
	"pOi!",
	"POi!",
	"poI!",
	"PoI!",
	"pOI!",
	"POI!",

	//16
	"poi?",
	"Poi?",
	"pOi?",
	"POi?",
	"poI?",
	"PoI?",
	"pOI?",
	"POI?",

	//8
	"poi",
	"Poi",
	"pOi",
	"POi",
	"poI",
	"PoI",
	"pOI",
	"POI"
};

// переписать. Желательно с использованием std::map

// переписать параметры, желательно использовать ссылку
std::string Poinator::Core::Transformation::ASCII::toPoi2(std::vector<unsigned char> byteCode)
{
	std::string exitPoiString;

	// переписать цикл
	while (!byteCode.empty())
	{
		exitPoiString += poiStrings[(size_t)byteCode[0]] + ' ';
		byteCode.erase(byteCode.begin());
	}

	return exitPoiString;
}

std::vector<unsigned char> Poinator::Core::Transformation::ASCII::fromPoi2(std::string poiText)
{
	std::vector<unsigned char> hardStringExit;

	poiText.erase(std::remove(poiText.begin(), poiText.end(), ' '), poiText.end());

	// разбить строку по Pp символам на массив и работать с ним через map
	while (poiText != "")
	{
		bool isErr = true;
		for (int i = 0; i < poiStrings.size(); i++)
		{
			auto size = poiStrings[i].size();
			std::string test = poiText.substr(0, size);
			if (test == poiStrings[i])
			{
				hardStringExit.push_back(static_cast<unsigned char>(i));
				poiText.erase(0, size);
				isErr = false;
				break;
			}
		}
		if (isErr)
			throw std::runtime_error("Decoding error - wrong poi text!");
	}

	return hardStringExit;
}

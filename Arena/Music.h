#pragma once

#include <chrono>
#include <thread>

#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523 // Wy¿sze C

// Definicje d³ugoœci nut (w milisekundach)
#define CALA 1000
#define POLNUTA 500
#define CWIARTKA 250
#define OSEMKA 125

void PlayMusic()
{
	auto play = [](auto f, auto t) { Beep(f, t); };

	play(G4, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(G4, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(G4, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(E4, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	play(C5, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(C5, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(C5, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(G4, CWIARTKA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	play(E4, POLNUTA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(D4, POLNUTA);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	play(C4, CALA);
}
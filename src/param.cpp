///
/// \file	param.cpp
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///

#include "param.h"

/// === INCLUDES	================================================================================

/// === NAMESPACES	================================================================================

float Param::Pi = 3.14159265358979;
float Param::HalfPi = Pi / 2;
float Param::TwoPi = Pi * 2;

uint16_t Param::framerate = 60;
uint16_t Param::window_width = 800;
uint16_t Param::window_height = 800;
uint16_t Param::scale = 10;

uint16_t Param::n_fish = 30;
uint16_t Param::n_food = 200;

uint16_t Param::n_inputs = 4;
uint16_t Param::n_outputs = 2;
uint16_t Param::n_hidden_layers = 2;
uint16_t Param::n_neurons_per_hidden_layer = 6;
float Param::activation_response = 1;
float Param::bias = -1;

float Param::turn_rate_max = 0.3;

uint32_t Param::n_ticks = 2000;
float Param::mutation_rate = 0.1;
float Param::crossover_rate = 0.7;
float Param::perturbation_max = 0.3;
uint16_t Param::n_elite = 4;
uint16_t Param::n_copies_elite = 1;

/// === PUBLIC DEFINITIONS	========================================================================

/// === PRIVATE DEFINITIONS	========================================================================

/// === END OF FILES	============================================================================

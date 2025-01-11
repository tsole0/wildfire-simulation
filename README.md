**Toy wildfire simulation to study effects of parameters on emergent systems. (Unoptimized)**

<img src="wildfire.gif" alt="Gif of wildfire simulation running" class="center" width="500"/>

---
## Goal
The goal of this project was to create a system of emergent large scale properties (wildfires) by only creating simple rules that are applied on small scales.

## Outcome
The simulation provides outcomes that demonstrate the great importance of initial parameterization for the simulation's outcome. The simulation only progresses in a manner resembling a natural forest fire for a narrow band of parameters, which include the growth rate of the forest and chance of catching fire based on neighboring fires.

The simulation is sucessful in demonstrating the effect of long-range, mobile phenomena despite the simulation of stationary objects (a cell grid).

*The program is my first project in C++ and suffers from memory leaks.*

## Properties

Simulates growth and death of a forest represented by 100x100 cell grid. Each cell has a 'growth' property, signifying the plant growth density of that area of forest. Each iteration, each cell has a small chance to spontaneously ignite that becomes larger the higher the cell's growth value becomes. If caught on fire, each cell will have a flame intensity that decays quickly. Each iteration, a cell checks its surrounding cells for fire and will determine its chance of catching fire from its growth level and fire's intensity of surrounding cells.

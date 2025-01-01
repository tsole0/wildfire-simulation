# Rules

## Cell Values

For each cell,

Fire Risk: 0.00-1.00
Flame Intensity: 0.00-1.00

## Rates

Each generation, every cell's fire risk increases by 0.02-0.05
Each generation, every cell's flame intensity decreases by 0.2

## New Generation

Every round, the chance that a cell catches fire is the cell's fire risk plus the average flame intensity of the eight cells surrounding it.
If a cell catches fire, its fire risk becomes zero and its flame intensity becomes one.
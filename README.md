# tqdm-lua
 (unofficial) tqdm-like lua pretty progress bar

#### iteator function
```lua
local tqdm = require "tqdm"

local sumPairs = 0
for i in tqdm.ipairs({1,2,3,4,5}) do
   sumPairs = sumPairs + i 
end

local sumRange = 0
for i in tqdm.range(5,1,-1) do
   sumRange = sumRange + i
end
assert(sumPairs == sumRange)

```

#### use progress method directly
```lua
local tqdm = require "tqdm"

local N = 100000000
local bar = tqdm.new(N)
for i=1,N do
	bar:progress(i)
end
```

additionally you can select a different them for the bar
```lua
local themedBar = tqdm.new(1000):theme("circle")
```
####available theme
![available theme](theme.png)

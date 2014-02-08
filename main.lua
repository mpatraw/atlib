
local at = require('at')

at.seed(os.time())

for i = 1, 10 do
        print(at.rand())
end

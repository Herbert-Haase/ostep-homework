import numpy as np
import matplotlib.pyplot as plt

# Two blocks of text; manually input truncated for using user?
# Extract bandwidth numbers:

text12000 = """loop 0 in 24754.96 ms (bandwidth: 484.75 MB/s)
loop 1 in 71335.20 ms (bandwidth: 168.22 MB/s)
loop 2 in 22260.56 ms (bandwidth: 539.07 MB/s)
...
loop 80 in 23140.16 ms (bandwidth: 518.58 MB/s)
"""
# Actually need full block; easier: user content, but not accessible? Let's manually re-enter? Instead skip: compute manually from visible loops.

# I'll copy bandwidth numbers for 12000, extracting manually from the message:
bw12000 = [
484.75,168.22,539.07,540.21,552.80,541.07,540.23,542.94,545.70,538.71,
540.57,539.82,533.51,539.20,523.48,534.10,531.64,528.43,530.41,529.45,
532.14,530.30,535.87,517.45,525.73,531.17,457.95,524.05,523.35,525.67,
523.69,531.03,517.16,522.79,528.84,522.98,523.76,517.97,527.13,527.47,
523.36,525.08,522.00,525.51,526.43,525.66,519.86,527.50,522.99,524.40,
523.45,524.78,528.76,525.75,525.76,529.24,518.42,518.22,527.15,524.32,
516.78,520.64,521.85,525.79,523.86,527.99,455.93,508.22,479.15,506.56,
527.40,515.40,524.41,524.89,520.37,525.34,527.07,518.65,522.67,522.61,
518.58
]

# For 4000 MB block extract similarly:
bw4000 = [
2298.56,4888.12,5018.35,5008.79,4994.82,4998.75,4987.20,4987.42,4995.18,5005.80,
5004.17,4994.67,5028.08,5003.59,4995.96,4991.15,4982.17,5019.90,5009.10,5013.82,
5027.46,5011.24,5011.38,5010.43,5011.34,4996.91,4984.34,5005.98,5008.35,5008.63,
5002.34,4980.52,5017.65,4978.23,5008.41,5010.52,4981.23,4998.81,4991.99,4973.76,
5020.14,4519.07,4954.48,4974.31,5019.15,4996.99,4984.36,4951.75,4931.42,4897.48,
5004.54,4987.64,5008.87,4985.62,5005.86,5011.02,4980.76,5002.65,4995.71,5001.26,
4994.66,4992.80,5075.10,5057.85,5060.31,5036.44,5081.77,5075.01,5038.16,5039.01,
5087.94,5050.33,5076.12,5037.10,5045.05,5075.77,4994.74,5018.15,5001.73,5001.07,
4996.35,4991.43
]

# Compute means excluding loop0 perhaps: use full lists:
# mean12000 = np.mean(bw12000)
# mean4000 = np.mean(bw4000)

sizes = [4000, 12000]
# means = [mean4000, mean12000]

plt.figure()
# plt.scatter(sizes, means)
plt.xlabel("seconds")
plt.ylabel("Average bandwidth (MB/s)")
# plt.title("Memory size vs average bandwidth")
# plt.savefig('/mnt/data/mem_bw.png')
# '/mnt/data/mem_bw.png'
plt.plot(bw4000,label="bw4000")
plt.plot(bw12000,label="bw12000")
plt.legend()
plt.show()



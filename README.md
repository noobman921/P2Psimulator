# P2Psimulator
---
* 考虑先cpp写demo然后用pybind11联调，或许可以用别的方法
* 建立邻接表然后用加权图找最短路实现 **c)	任何两个顶点之间的网络连接的传输速率和节点之间距离成反比，传输速率的取值范围是[20Kbyte/s, 100Kbyte/s]**
* 或许某些地方可以换成队列 **可基于队列实现“离散事件模拟”，可通过百度、google、电子图书馆等方式获取网络模拟相关知识**
---
## cppPart todo
- [ ] a)	网络中包含N个客户端顶点（N >= 100），1个服务器顶点。每个客户端/服务器随机分配一个二维平面中的坐标(x, y) 用于描述该客户端/服务器的地理位置。
- [ ] b)	每个客户端或服务器随机挑选网络中的t个客户端或服务器，建立到它们的网络连接。
- [ ] c)	任何两个顶点之间的网络连接的传输速率和节点之间距离成反比，传输速率的取值范围是[20Kbyte/s, 100Kbyte/s]。
- [ ] d)	服务器每秒产生的视频数据的大小是30Kbyte。视频数据被切分为等大的数据块，每个数据块的大小为1Kbyte。每个数据块都对应一个全局唯一的整数序号，该序号反映数据块产生的时间先后。例如，第一个数据块序号为1，第二个数据块序号为2，依此类推。
- [ ] e)	每个客户端会定期检测它的邻居节点拥有的数据块序号，并向邻居节点请求自己没有的数据块。邻居节点收到请求后，会将对应的数据块传给该客户端。（本次模拟实验中，可忽略发起请求所需要消耗的时间）.
- [ ] f)	客户端可以连续播放的前提是拥有连续的完整的M个分块 (M>= 5)。也即是客户端能播放数据块i的前提是，该客户端已经下载了数据块i, i+1, i+2,…, i+M-1.
- [ ] g)	每个客户端可缓存N个数据分块，（N可自由配置）。在客户端上维护一个长度为N的缓存队列，新到达的数据分块会将最老的数据块进行覆盖。
---
2025/3/7
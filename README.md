# [CoAP](https://github.com/qitas/CoAP) 

#### qitas@qitas.cn

## [描述](https://github.com/qitas/CoAP/wiki) 

CoAP协议基于REST 构架，为了克服HTTP对于受限环境的劣势，CoAP既考虑到数据报长度的最优化，又考虑到提供可靠通信。

CoAP重新设计了HTTP的部分功能以适应设备的约束条件。另外，为了使协议适应物联网和M2M 应用，CoAP协议改进了一些机制，同时增加了一些功能。

- CoAP提供URI，REST式的方法如GET，POST，PUT和DELETE，以及可以独立定义的头选项提供的可扩展性。
- CoAP基于轻量级的UDP协议，并且允许IP多播。

为了弥补UDP传输的不可靠性，CoAP定义了带有重传机制的事务处理机制。并且提供资源发现机制，并带有资源描述。CoAP协议采用了双层的结构。事务层(Transaction layer)处理节点间的信息交换，同时，也提供对多播和拥塞控制的支持。请求/响应层(Request/Response layer)用以传输对资源进行操作的请求和相应信息。

#### [维基百科描述](http://en.wikipedia.org/wiki/Constrained_Application_Protocol) 


### [NB方案](NB/)

#### [BC26实现](NB/)


---

### 锻造最美之器

[![sites](qitas/qitas.png)](http://www.qitas.cn)

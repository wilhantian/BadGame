BadGame 《烂游戏》
===================================
   by WilhanTian   email wilhan.tian@gmail.com
   
   本游戏使用cocos2d-x 3.2 Final版本开发。
   为了节省git同步时间，我只保留了Classes文件夹和Res资源文件夹。
   
   最开始打算直接使用cocos2d-x3.X内部封装好的物理精灵，不过两个物体碰撞会出现互相嵌入的现象，
想了好久也没有头绪怎样解决~ 然后我就毅然决然的使用了Box2d物理引擎，将2d-x中的Sprite和Box2D的
刚体进行封装。
   另外我也将Box2d的碰撞事件进行了分发回调，从而大大减少了耦合度。

p.s. 本人职业学生，代码稚嫩、和各种不标准的地方，还请大家见谅！
and p.s. 所有BadGame的图片资源大多都来自共享的资源，所以我没有资格把它们据为己有。故任何人都可以复制，修改，重新发表，甚至以自己的名义发表，我都不会追究，但你在做以上事情的时候必须保证内容的完整性。最后，任何人不能以这些源码与资源的任何部分，谋取任何形式的报酬。

主要类说明：
----------------------------
ConfigData  单例 通过此类获取各种配置信息 <br/> 
DynamicData  单例 动态数据类<br/>
GameManager  单例 游戏管理器 用来驱动游戏和物理引擎 封装事件的分发在此实现<br/>
GameObject  游戏对象  /*这个不用解释了吧？*/<br/>
JINTools   JNI相关的东西 大部分是静态方法  这个JINTools的名字当时写错了...应该是JNITools...哈哈！<br/>
LifeObject    具有生命的对象<br/>
MapAnalysis   游戏地图解析类  就是专门用来解析地图的，我是用TiledMap做的游戏地图编辑器~~<br/>
PhysicsSprite   物理精灵  将Sprite和box2d进行了二次封装<br/>
StaticData    静态数据类 废弃了...<br/>
StaticDataEx  静态数据类<br/>
TextData   专门保存字符串数据的<br/>

 ![image](https://github.com/wilhantian/BadGame/blob/master/_image/1.png)
  ![image](https://github.com/wilhantian/BadGame/blob/master/_image/2.png)
   ![image](https://github.com/wilhantian/BadGame/blob/master/_image/5.png)
    ![image](https://github.com/wilhantian/BadGame/blob/master/_image/6.png)

[好乎-好玩的不亦乐乎](http://www.hahuu.com)
[498工具盒子](http://www.498box.com)

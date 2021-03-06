#pragma once
#include "stdafx.h"
#include "Space.h"
namespace SpaceGameEngine
{
	class Object;

	class Component							//组件：用于继承的基类
	{
	public:
		Component();
		~Component();
		std::string GetTypeName();			//获取类型名
		Component* GetFatherComponent();	//获取父组件
		void SetFatherComponent(Component* pc);//设置父组件
		void AddChildComponent(Component* pc);	//添加子组件
		bool DeleteChildComponent(Component* pc);	//删除子组件
		Component* FindChildComponent(const std::string& name);	//在所有子组件中寻找类型为name的组件(BFS)
		std::vector<Component*>& GetChildrenComponent();	//获得子组件数组的引用
		virtual void InitFromFile(const std::string& filename, int mode = 0);
		virtual void Start();			//在开始时执行
		virtual void Run(float DeltaTime);//每帧运行时的操作
		virtual void Attach(Component* pc);	//成为...组件的依附
		virtual void Release();				//释放
		bool IfRun();						//是否每帧运行
		bool IfUse();						//是否使用
		void ChangeIfRun(bool b);			//更改每帧是否运行
		void ChangeIfUse(bool b);			//更改是否使用
		void SetFatherObject(Object* po);			//设置所属的Object对象
		Object* GetFatherObject();				//获取所属的Object对象
	protected:
		std::string m_TypeName;				//组件的类型名
		bool m_IfRun;						//是否每帧运行
		bool m_IfUse;						//是否使用
		std::vector<Component*> m_Children;	//子组件
		Component* m_pFather;				//父组件
		Object* m_pFatherObject;					//所属的Object对象
	};
}
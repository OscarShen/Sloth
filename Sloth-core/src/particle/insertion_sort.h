/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_INSERTION_SORT_H_
#define SLOTH_INSERTION_SORT_H_
#include <sloth.h>
#include "particle.h"
namespace sloth {

	class InsertionSort
	{
	public:
		/***********************************************************************
		* @description	: 对粒子进行插入排序，因为粒子每一帧间的变化并不大，优先使用
						  插入排序
		* @author		: Oscar Shen
		* @creat		: 2017年3月7日10:24:57
		***********************************************************************/
		static void sortHighToLow(std::list<std::shared_ptr<Particle>> &particles);

	private:
		static void sortUpHighToLow(std::list<std::shared_ptr<Particle>> &particles, std::list<std::shared_ptr<Particle>>::iterator it);
	};

}


#endif // !SLOTH_INSERTION_SORT_H_

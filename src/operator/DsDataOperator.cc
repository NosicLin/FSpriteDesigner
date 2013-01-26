#include "DsDataOperator.h"

DataOperator::DataOperator()
{
	m_data=DsData::shareData();
}
DataOperator::setCurProject(DsProject* prog)
{
	m_data->setCurProject(prog);
	m_data->emitSignal(SG_CUR_PROJECT_CHANGE);
}

DataOperator::setCurAnimation(const std::string& anim)
{
	m_data->setCurAnimation(anim);
	m_data->emitSignal(SG_CUR_ANIMATION_CHANGE);
}

DataOperator::setCurFrame(int frame)
{
	m_data->setCurFrame(frame);
	m_data->emitSignal(SG_CUR_FRAME_CHANGE);
}

DataOperator::setCurFrameImage(const std::string& anim)
{
	m_data->setCurFrameImage(anim);
	m_data->emitSignal(SG_CUR_FRAME_IMAGE_CHANGE);
}

DataOperator::addAnimation(const std::string& anim)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
	{
		sprite->addAnimation(anim);
		m_data->emitSignal(SG_SPRITE_PROPERTY_CHANGE);
	}
}

DataOperator::removeAnimation(const std::string& anim)
{
	DsSprite* sprite=m_data->getCurSprite();
	if(sprite)
	{
		/*TODO*/
	}
}




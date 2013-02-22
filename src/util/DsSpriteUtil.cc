#include <QtXml>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <string>

#include "model/DsModel.h"
#include "DsUtil.h"
#include "DsSpriteUtil.h"
#include "DsDebug.h"


DsProject* DsSpriteUtil::loadProject(const std::string& path,std::string& msg)
{
	QFile file(path.c_str());
	if(!file.open(QFile::ReadOnly|QFile::Text))
	{
		msg="Open File Failed";
		return NULL;
	}

	QDomDocument doc;
	QString errstr;
	int errline, errcol;
	if(!doc.setContent(&file,false,&errstr,&errline,&errcol))
	{
        msg=DsUtil::qtos(errstr+QString("(")+
				QString::number(errline)+QString(",")+
				QString::number(errcol)+QString(")"));
		return NULL;
	}

	QDomElement root=doc.documentElement();
	if(root.nodeName()!=QString("FSpriteDesigner"))
	{
		msg="Err File Type";
		return NULL;
    }
    if(root.attribute("version")!=QString("v1.0"))
    {
        msg="version not support";
        return NULL;
    }
    if(root.attribute("type")!=QString("sprite"))
    {
        msg="Unsupport file type";
        return NULL;
    }
    std::string proj_name=DsUtil::qtos(root.attribute("name"));
    DsSprite* sprite=new DsSprite("fsf");
    QDomNodeList anims=doc.elementsByTagName("animation");
    for(int i=0;i<anims.count();i++)
	{
		DsAnimation* anim=loadAnimation(anims.item(i));
		if(anim!=NULL)
		{
			sprite->addAnimation(anim);
		}
    }
    return NULL;
    //DsProject* proj=new DsProject(sprite,proj_name);;
    //return proj;
}
DsAnimation* DsSpriteUtil::loadAnimation(QDomNode node)
{
	QDomElement element=node.toElement();
	QString anim_name=element.attribute("name");
    DsAnimation* anim=new DsAnimation(DsUtil::qtos(anim_name));

	QDomNodeList frames=element.childNodes();
	for(int i=0;i<frames.count();i++)
	{
		QDomNode f=frames.item(i);
        DsFrame* ds_frame=loadFrame(f);
		if(ds_frame!=NULL)
		{
			anim->pushFrame(ds_frame);
		}
	}
	return anim;
}

DsFrame* DsSpriteUtil::loadFrame(QDomNode node)
{
	QDomElement element=node.toElement();
	int frame_id=element.attribute("id").toInt();
	QString frame_type=element.attribute("type");
    if(frame_type=="key")
	{
		DsKeyFrame* f=new DsKeyFrame(frame_id);
		QDomNodeList images=element.childNodes();
		for(int i=0;i<images.count();i++)
		{
			DsFrameImage* img=loadFrameImage(images.item(i));
			if(img)
			{
				f->pushFrameImage(img);
			}
		}
		return  f;
	}
	else if(frame_type=="tween")
	{
        return new DsTweenFrame(NULL,NULL,frame_id);
	}
	else 
    {
        DsDebug<<"UnKown Frame Type,Ingnore"<<endl;
        return NULL;
	}
}

DsFrameImage* DsSpriteUtil::loadFrameImage(QDomNode node)
{
    float tx=0,ty=0,sx=1,sy=1,angle=0;
    float areax0=0,areay0=0,areax1=1,areay1=1;
    std::string url;
    tx=node.firstChildElement("posx").text().toFloat();
    ty=node.firstChildElement("posy").text().toFloat();
    sx=node.firstChildElement("scalex").text().toFloat();
    sy=node.firstChildElement("scaley").text().toFloat();
    angle=node.firstChildElement("angle").text().toFloat();

    areax0=node.firstChildElement("areax0").text().toFloat();
    areay0=node.firstChildElement("areay0").text().toFloat();
    areax1=node.firstChildElement("areax1").text().toFloat();
    areay1=node.firstChildElement("areay1").text().toFloat();
    url=node.firstChildElement("url").text().toStdString();

    DsFrameImage* ret=DsFrameImage::create(url);
    ret->setPos(tx,ty);
    ret->setAngle(angle);
    ret->setScale(sx,sy);
    ret->setTextureArea(areax0,areay0,areax1,areay1);

    return ret;
}

void DsSpriteUtil::saveProject(DsProject* proj,QXmlStreamWriter& writer)
{
    /*
	writer.writeStartDocument();
	writer.writeStartElement("FSpriteDesigner");
	writer.writeAttribute("version","v1.0");
    writer.writeAttribute("type","sprite");
    writer.writeAttribute("name",proj->getRealName().c_str());

    DsSprite* sprite=proj->getSprite();

    for(int i=0;i<sprite->getAnimationNu();i++)
	{
        DsAnimation* animation=sprite->getAnimation(i);
		writeAnimation(animation,writer);
	}
    writer.writeEndElement();
    */

}
void DsSpriteUtil::writeAnimation(DsAnimation* animation,QXmlStreamWriter& writer)
{
	writer.writeStartElement("animation");
	writer.writeAttribute("name",animation->getName().c_str());
	DsAnimation::Iterator iter;
	for(iter=animation->begin();iter!=animation->end();iter++)
	{
		writeFrame(*iter,writer);
	}
	writer.writeEndElement();
}
void DsSpriteUtil::writeFrame(DsFrame* frame,QXmlStreamWriter& writer)
{
	writer.writeStartElement("frame");
	writer.writeAttribute("id",QString::number(frame->getFrameId()));
	if(frame->getType()==DsFrame::FRAME_KEY)
	{
		writer.writeAttribute("type","key");

		DsKeyFrame* key_frame=(DsKeyFrame*)frame;
		DsKeyFrame::Iterator iter=key_frame->begin();
		for(;iter!=key_frame->end();++iter)
		{
			writeFrameImage(*iter,writer);
		}
	}
	else 
	{
		writer.writeAttribute("type","tween");
	}
	writer.writeEndElement();
}
void DsSpriteUtil::writeFrameImage(DsFrameImage* image,QXmlStreamWriter& writer)
{
	writer.writeStartElement("frameimage");
	writer.writeTextElement("url",image->getImage()->name.c_str());
	writer.writeTextElement("posx",QString::number(image->getPosX()));
	writer.writeTextElement("posy",QString::number(image->getPosY()));
	writer.writeTextElement("scalex",QString::number(image->getScaleX()));
	writer.writeTextElement("scaley",QString::number(image->getScaleY()));
	writer.writeTextElement("angle",QString::number(image->getAngle()));

    float ax0,ay0,ax1,ay1;
	image->getTextureArea(&ax0,&ay0,&ax1,&ay1);

	writer.writeTextElement("areax0",QString::number(ax0));
	writer.writeTextElement("areay0",QString::number(ay0));
	writer.writeTextElement("areax1",QString::number(ax1));
	writer.writeTextElement("areay1",QString::number(ay1));

	writer.writeEndElement();
}
























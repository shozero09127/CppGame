/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	width = visibleSize.width;
	height = visibleSize.height;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        //this->addChild(sprite, 0);
    }

	
		// OpenGL�̃G���[�R�[�h���󂯂�ϐ�
		GLenum error;
	m_pProgram = new GLProgram;
	// �V�F�[�_���e�L�X�g�t�@�C������ǂ݂���ŃR���p�C��
	m_pProgram->initWithFilenames("shaders/shader_0tex.vsh", "shaders/shader_0tex.fsh");
	error = glGetError();
	// attribute�ϐ��ɑ����C���f�b�N�X������U��
	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	error = glGetError();
	//attribute�ϐ��ɑ���index������U��
	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	error = glGetError();
	// �V�F�[�_�v���O�����������N
	m_pProgram->link();
	error = glGetError();
	// uniform�ϐ��̃��X�g��ۑ�
	m_pProgram->updateUniforms();
	error = glGetError();
	//Update�̗L��
	this->scheduleUpdate();
    return true;
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	GLenum error;
	// �w�肵���t���O�ɑΉ����鑮���C���f�b�N�X������L���ɂ��āA���͖����ɂ���
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION|GL::VERTEX_ATTRIB_FLAG_COLOR);
	error = glGetError();
	// �V�F�[�_�[��L��������
	m_pProgram->use();
	error = glGetError();
	// �O�p�`�̂R���_���̍��W
	Vec3 pos[4];
	Vec3 color[4];
	const float x = 0.5f;
	const float y = 0.5f;
	// ���W���P�_���ݒ�
	pos[0] = Vec3(-x, -y, 0);
	pos[1] = Vec3(-x, y, 0);
	pos[2] = Vec3(x, -y, 0);
	pos[3] = Vec3(x, y, 0);
	//�J���[��1�_���ݒ�
	color[0] = Vec3(0, 0, 0);
	color[1] = Vec3(1, 0, 0);
	color[2] = Vec3(0, 1, 0);
	color[3] = Vec3(0, 0, 1);
	// �w�肵�������C���f�b�N�X�ɁA�f�[�^���֘A�t����
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, pos);
	// �w�肵�������C���f�b�N�X�ɁA�f�[�^���֘A�t����
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, 0, color);
	error = glGetError();
	// 3���_���̃f�[�^�ŎO�p�`��`�悷��
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glDrawArrays(GL_QUADS, 0, 4);//��������4�_���_�̎l�p�`�͔񐄏��Ȃ̂ō���͕p�o�����Ȃ��B
	error = glGetError();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}



//
//  ActionTopScene.cpp
//  Action
//
//  Created by MAEDAHAJIME on 2015/02/09.
//
//

#include "ActionTopScene.h"

USING_NS_CC;

// _/_/_/ コンストラクタ プロパティー _/_/_/
ActionTopScene::ActionTopScene()
: _label11(NULL)
, _label12(NULL)
{
    
}

// MainScene デストラクタで解放 メモリーリークを防ぐ
ActionTopScene::~ActionTopScene()
{
    CC_SAFE_RELEASE_NULL(_label11); // _label11をreleaseしてメモリーリークを防ぎます
    CC_SAFE_RELEASE_NULL(_label12); // _label12をreleaseしてメモリーリークを防ぎます
}

// createSceneはLayerをSceneに貼り付けて返すクラスメソッドです。
// 自分自身(ActionTopScene)を生成し、空のSceneに貼り付けて返す簡単な処理を行っているだけです。
// これでほかのシーンからの遷移が楽に行えます。
Scene* ActionTopScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ActionTopScene::create();
    scene->addChild(layer);
    return scene;
}

bool ActionTopScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    // 初期化処理
    
    // バックグラウンド
    Background();
        
    // 回転ラベル表示メソッド
    rotationLabel();
    
    // ラベルボタン表示メソッド
    buttonBorn();
    
    return true;

}

// バックグランド
void ActionTopScene::Background()
{
    
    // 画面サイズを取得
    auto winSize = Director::getInstance()->getVisibleSize();
    
    // バックグランドカラー
    auto background = LayerColor::create(Color4B::BLUE,
                                         winSize.width,
                                         winSize.height);
    // ラベルを生成
    auto label1 = Label::createWithSystemFont("Action 回転 移動 拡大", "Arial", 80);
    
    // ラベルの設置
    label1->setPosition(Vec2(winSize.width / 2 ,winSize.height / 2 + 270));
    
    // ラベルタイトルを追加
    this->addChild(label1,1);
    
    // バックグランドカラー 第2引数は表示順
    this->addChild(background, 0);
}

// 回転ラベル表示メソッド
void ActionTopScene::rotationLabel()
{
    // 画面サイズを取得
    Size winSize = Director::getInstance()->getVisibleSize();
    
    // ラベルを生成
    _label11 = Label::createWithSystemFont("Rotation", "Marker Felt", 60);
    
    // ラベルの設置
    _label11->setPosition(Vec2(winSize.width/4 ,winSize.height/2));
    
    // ラベルタイトルを追加
    this->addChild(_label11,1);
    
    // 回転角度を指定する(setRotation)
    _label11->setRotation(45);
    
    // ラベルを生成
    _label12 = Label::createWithSystemFont("Rotation", "Marker Felt", 60);
    
    // ラベルの設置
    _label12->setPosition(Vec2(winSize.width - winSize.width/4 ,winSize.height/2));
    
    // ラベルタイトルを追加
    this->addChild(_label12,1);
    
    // 回転角度を指定する(setRotation)
    _label12->setRotation(45);
}

// ラベルボタン表示メソッド
void ActionTopScene::buttonBorn()
{
    
    // 画面サイズを取得
    auto winSize = Director::getInstance()->getVisibleSize();
    
    // ラベルを生成
    //Ver3.x CC_CALLBACK_1 マクロ（引数が１つ）にすること
    auto labelBtnLabel01 = Label::createWithSystemFont("（左）Action RotateTo", "Arial", 48);
    // ラベルメニューアクション先の設定
    auto labelItem01 = MenuItemLabel::create(labelBtnLabel01,
                                             CC_CALLBACK_1(ActionTopScene::BtDidPushed, this));
    
    // ラベルメニュー1タグをセット
    labelItem01->setTag(1);
    
    // ラベルを生成
    auto labelBtnLabel02 = Label::createWithSystemFont("（右）Action RotateBy", "Arial", 48);
    // ラベルメニューアクション先の設定
    auto labelItem02 = MenuItemLabel::create(labelBtnLabel02,
                                             CC_CALLBACK_1(ActionTopScene::BtDidPushed, this));
    
    // ラベルメニュー2タグをセット
    labelItem02->setTag(2);
    
    // 左ラベルの設置
    labelItem01->setPosition(Vec2(winSize.width/2 - 300,winSize.height/2 - 260));
    // 右ラベルの設置
    labelItem02->setPosition(Vec2(winSize.width/2 + 300,winSize.height/2 - 260));
    
    
    // メニューを作成 自動解放オブジェクト
    auto menu = Menu::create(labelItem01,labelItem02,NULL);
    
    menu->setPosition(Point::ZERO);
    // メニューを追加
    this->addChild(menu, 1);
}

// ボタンをタッチした時の用のメソッド
void ActionTopScene::BtDidPushed(Ref *pSender)
{
    // pSender menuItemに型変換
    MenuItem* menuItem = (MenuItem*)pSender;
    
    // タグ番号GETで判定
    switch(menuItem->getTag())
    {
        case 1:
            
            CCLOG("RotateTo");
            
            // アクションToメソッド 指定した数値まで動作する
            actionTo();
            break;
            
        case 2:
            
            CCLOG("RotateBy");
            
            // アクションByメソッド 現在の位置 + 指定した数値まで動作し何度でも動作を繰り返す
            actionBy();
            break;
    }
}

// アクションToメソッド 指定した数値まで動作する
void ActionTopScene::actionTo()
{
    // CCActionRotateTo 3秒 45度に180度を加算した225度まで回転
    auto rotateTo = RotateTo::create(3.0f, 180.0f);
    
    // 「指定した座標」まで移動させます
    auto moveTo = MoveTo::create(3, Vec2(30, _label11->getPositionY()));
    
    //    // 大きさ（拡大）アクションを適用 2秒 3倍
    //    auto scaleTo = ScaleTo::create(2.0f, 3.0f);

    //    //「指定した座標」までジャンプしながら移動します
    //    auto jumpTo = JumpTo::create(3, Vec2(200, 10), 60, 5);

    // 回転、移動アクションを適用
    auto sequence = Sequence::create(rotateTo, moveTo, NULL);
    
    // 回転、移動アクションを適用
    _label11->runAction(sequence);

}

// アクションByメソッド 現在の位置 + 指定した数値まで動作し何度でも動作を繰り返す
void ActionTopScene::actionBy()
{
    // CCActionRotateBy 3秒 45度に180度を加算した225度まで回転
    auto rotateBy = RotateBy::create(3.0f, 180.0f);
    
    // 「指定した座標」まで移動させます
    auto moveBy = MoveBy::create(3, Vec2(30, _label11->getPositionY()));
    
    //    // 大きさ（拡大）アクションを適用 2秒 3倍
    //    auto scaleBy = ScaleBy::create(2.0f, 3.0f);

    //    //「指定した座標」までジャンプしながら移動します
    //    auto jumpBy = JumpBy::create(3, Vec2(200, 10), 60, 5);
    
    // 回転、移動
    auto sequence = Sequence::create(rotateBy, moveBy, NULL);
    
    // 回転、移動アクションを適用
    _label12->runAction(sequence);
}





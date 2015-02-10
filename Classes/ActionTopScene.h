//
//  ActionTopScene.h
//  Action
//
//  Created by MAEDAHAJIME on 2015/02/09.
//
//

#ifndef __Action__ActionTopScene__
#define __Action__ActionTopScene__

#include "cocos2d.h"

class ActionTopScene :public cocos2d::Layer
{
protected:
    // コンストラクタ
    ActionTopScene();
    // デストラクタ
    virtual ~ActionTopScene();
    // メソッド CREATE_FUNCとの連携
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    
    // バックグラウンド
    void Background();
    
    // ボタン表示メソッド
    void buttonBorn();
    
    // ボタンをタッチした時の用のメソッド Object →　Ref に変更
    void BtDidPushed(Ref *pSender);
    
    // 回転ラベル表示メソッド
    void rotationLabel();
    
    // アクションToメソッド 指定した数値まで動作する
    void actionTo();
    
    // アクションByメソッド 現在の位置 + 指定した数値まで動作し何度でも動作を繰り返す
    void actionBy();
    
    CREATE_FUNC(ActionTopScene);
    
    // _/_/_/ プロパティー _/_/_/
    // 頻繁に他の場所から参照するためメンバー変数としてシーンクラスに保持させる
    //　_label11変数と、getLabel11()メソッド、setLabel11(Label *)メソッドが自動的に実装される
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _label11, Label11);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _label12, Label12);
    
};

#endif /* defined(__Action__ActionTopScene__) */


#pragma once

#include <iostream>

//	AVL树头必须为指针
template <typename DT>
class AVL树 {
private: //	数据
    DT     数据;
    int    高度;
    AVL树 *左子树;
    AVL树 *右子树;

    //	旋转
    void 自平衡调整(AVL树 *&根);
    void 左左旋转(AVL树 *&根);
    void 左右旋转(AVL树 *&根);
    void 右右旋转(AVL树 *&根);
    void 右左旋转(AVL树 *&根);
    void 删除最小值(AVL树 *&根, AVL树 *&temp);
    void 删除最大值(AVL树 *&根, AVL树 *&temp);
    //	更新高度
    void 更新高度();

public:
    AVL树(DT &数据); //	构造函数
    void                 插入(AVL树 *&根, DT &数据);
    void                 删除(AVL树 *&根, DT &数据);
    friend std::ostream &operator<<(std::ostream &输出, AVL树 &根节点);

    int 获取高度();
    int 获取平衡因子();
};

//	构造函数
template <typename DT>
AVL树<DT>::AVL树(DT &数据) {
    this->数据   = 数据;
    this->高度   = 1;
    this->左子树 = nullptr;
    this->右子树 = nullptr;
}

template <typename DT>
std::ostream &operator<<(std::ostream &输出, AVL树<DT> &根节点) {
    return 输出 << "数据:\t" << 根节点.数据 << std::endl
                << "高度:\t" << 根节点.高度 << std::endl
                << "左子树:\t" << 根节点.左子树 << std::endl
                << "右子树:\t" << 根节点.右子树 << std::endl;
}

template <typename DT>
void AVL树<DT>::插入(AVL树<DT> *&根, DT &数据) {
    if (!根)
        根 = new AVL树<DT>(数据);
    else {
        if (数据 < 根->数据)
            根->左子树->插入(根->左子树, 数据);
        else
            根->右子树->插入(根->右子树, 数据);
    }
    根->自平衡调整(根);
}

template <typename DT>
void AVL树<DT>::删除(AVL树<DT> *&根, DT &数据) {
    if (根) {

        if (数据 < 根->数据)
            根->左子树->删除(根->左子树, 数据);
        else if (数据 > 根->数据)
            根->右子树->删除(根->右子树, 数据);
        else {

            if (根->右子树)
                根->右子树->删除最小值(根->右子树, temp);
            else if (根->左子树)
                根->左子树->删除最大值(根->左子树, temp);
            else {
                AVL树<DT> *temp = nullptr;
                delete 根;
                根 = nullptr;

                if (temp) {
                    temp->左子树 = 根->左子树;
                    temp->右子树 = 根->右子树;
                    delete 根;
                    根 = temp;
                }
            }
        }
        根->自平衡调整(根);
    }
}

template <typename DT>
void AVL树<DT>::删除最小值(AVL树<DT> *&根, AVL树<DT> *&temp) {
    if (!根->左子树) {
        temp = 根;
        根   = 根->右子树;
    } else {
        根->左子树->删除最小值(根->左子树, temp);
        根->自平衡调整(根);
    }
}

template <typename DT>
void AVL树<DT>::删除最大值(AVL树<DT> *&根, AVL树<DT> *&temp) {
    if (!根->右子树) {
        temp = 根;
        根   = 根->左子树;
    } else {
        根->右子树->删除最大值(根->右子树, temp);
        根->自平衡调整(根);
    }
}

template <typename DT>
void AVL树<DT>::自平衡调整(AVL树<DT> *&根) {
    根->更新高度();
    int 平衡因子 = 根->获取平衡因子();

    if (平衡因子 > 1) {
        if (左子树->左子树->获取高度() > 左子树->右子树->获取高度())
            根->左左旋转(根);
        else
            根->左右旋转(根);
    } else if (平衡因子 < -1) {
        if (右子树->右子树->获取高度() > 右子树->左子树->获取高度())
            根->右右旋转(根);
        else
            根->右左旋转(根);
    }
}

template <typename DT>
int AVL树<DT>::获取高度() {
    return (this) ? this->高度 : 0;
}
template <typename DT>
int AVL树<DT>::获取平衡因子() {
    return this->左子树->获取高度() - this->右子树->获取高度();
}

template <typename DT>
void AVL树<DT>::左左旋转(AVL树<DT> *&根) {
    根           = this->左子树;
    this->左子树 = 根->右子树;
    根->右子树   = this;
    this->更新高度();
    根->更新高度();
}

template <typename DT>
void AVL树<DT>::右右旋转(AVL树<DT> *&根) {
    根           = this->右子树;
    this->右子树 = 根->左子树;
    根->左子树   = this;
    this->更新高度();
    根->更新高度();
}

template <typename DT>
void AVL树<DT>::左右旋转(AVL树<DT> *&根) {
    根                   = this->左子树->右子树;
    this->左子树->右子树 = 根->左子树;
    根->左子树           = this->左子树;
    this->左子树         = 根->右子树;
    根->右子树           = this;

    根->左子树->更新高度();
    根->右子树->更新高度();
    根->更新高度();
}

template <typename DT>
void AVL树<DT>::右左旋转(AVL树<DT> *&根) {
    根                   = this->右子树->左子树;
    this->右子树->左子树 = 根->右子树;
    根->右子树           = this->右子树;
    this->右子树         = 根->左子树;
    根->左子树           = this;

    根->左子树->更新高度();
    根->右子树->更新高度();
    根->更新高度();
}

template <typename DT>
void AVL树<DT>::更新高度() {
    if (this) {
        int 左子树高度 = (左子树) ? 左子树->高度 : 0;
        int 右子树高度 = (右子树) ? 右子树->高度 : 0;
        this->高度     = 1 + ((左子树高度 > 右子树高度) ? 左子树高度 : 右子树高度);
    }
}

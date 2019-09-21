
#pragma once

#include <iostream>

//	AVL��ͷ����Ϊָ��
template <typename DT>
class AVL�� {
private: //	����
    DT     ����;
    int    �߶�;
    AVL�� *������;
    AVL�� *������;

    //	��ת
    void ��ƽ�����(AVL�� *&��);
    void ������ת(AVL�� *&��);
    void ������ת(AVL�� *&��);
    void ������ת(AVL�� *&��);
    void ������ת(AVL�� *&��);
    void ɾ����Сֵ(AVL�� *&��, AVL�� *&temp);
    void ɾ�����ֵ(AVL�� *&��, AVL�� *&temp);
    //	���¸߶�
    void ���¸߶�();

public:
    AVL��(DT &����); //	���캯��
    void                 ����(AVL�� *&��, DT &����);
    void                 ɾ��(AVL�� *&��, DT &����);
    friend std::ostream &operator<<(std::ostream &���, AVL�� &���ڵ�);

    int ��ȡ�߶�();
    int ��ȡƽ������();
};

//	���캯��
template <typename DT>
AVL��<DT>::AVL��(DT &����) {
    this->����   = ����;
    this->�߶�   = 1;
    this->������ = nullptr;
    this->������ = nullptr;
}

template <typename DT>
std::ostream &operator<<(std::ostream &���, AVL��<DT> &���ڵ�) {
    return ��� << "����:\t" << ���ڵ�.���� << std::endl
                << "�߶�:\t" << ���ڵ�.�߶� << std::endl
                << "������:\t" << ���ڵ�.������ << std::endl
                << "������:\t" << ���ڵ�.������ << std::endl;
}

template <typename DT>
void AVL��<DT>::����(AVL��<DT> *&��, DT &����) {
    if (!��)
        �� = new AVL��<DT>(����);
    else {
        if (���� < ��->����)
            ��->������->����(��->������, ����);
        else
            ��->������->����(��->������, ����);
    }
    ��->��ƽ�����(��);
}

template <typename DT>
void AVL��<DT>::ɾ��(AVL��<DT> *&��, DT &����) {
    if (��) {

        if (���� < ��->����)
            ��->������->ɾ��(��->������, ����);
        else if (���� > ��->����)
            ��->������->ɾ��(��->������, ����);
        else {

            if (��->������)
                ��->������->ɾ����Сֵ(��->������, temp);
            else if (��->������)
                ��->������->ɾ�����ֵ(��->������, temp);
            else {
                AVL��<DT> *temp = nullptr;
                delete ��;
                �� = nullptr;

                if (temp) {
                    temp->������ = ��->������;
                    temp->������ = ��->������;
                    delete ��;
                    �� = temp;
                }
            }
        }
        ��->��ƽ�����(��);
    }
}

template <typename DT>
void AVL��<DT>::ɾ����Сֵ(AVL��<DT> *&��, AVL��<DT> *&temp) {
    if (!��->������) {
        temp = ��;
        ��   = ��->������;
    } else {
        ��->������->ɾ����Сֵ(��->������, temp);
        ��->��ƽ�����(��);
    }
}

template <typename DT>
void AVL��<DT>::ɾ�����ֵ(AVL��<DT> *&��, AVL��<DT> *&temp) {
    if (!��->������) {
        temp = ��;
        ��   = ��->������;
    } else {
        ��->������->ɾ�����ֵ(��->������, temp);
        ��->��ƽ�����(��);
    }
}

template <typename DT>
void AVL��<DT>::��ƽ�����(AVL��<DT> *&��) {
    ��->���¸߶�();
    int ƽ������ = ��->��ȡƽ������();

    if (ƽ������ > 1) {
        if (������->������->��ȡ�߶�() > ������->������->��ȡ�߶�())
            ��->������ת(��);
        else
            ��->������ת(��);
    } else if (ƽ������ < -1) {
        if (������->������->��ȡ�߶�() > ������->������->��ȡ�߶�())
            ��->������ת(��);
        else
            ��->������ת(��);
    }
}

template <typename DT>
int AVL��<DT>::��ȡ�߶�() {
    return (this) ? this->�߶� : 0;
}
template <typename DT>
int AVL��<DT>::��ȡƽ������() {
    return this->������->��ȡ�߶�() - this->������->��ȡ�߶�();
}

template <typename DT>
void AVL��<DT>::������ת(AVL��<DT> *&��) {
    ��           = this->������;
    this->������ = ��->������;
    ��->������   = this;
    this->���¸߶�();
    ��->���¸߶�();
}

template <typename DT>
void AVL��<DT>::������ת(AVL��<DT> *&��) {
    ��           = this->������;
    this->������ = ��->������;
    ��->������   = this;
    this->���¸߶�();
    ��->���¸߶�();
}

template <typename DT>
void AVL��<DT>::������ת(AVL��<DT> *&��) {
    ��                   = this->������->������;
    this->������->������ = ��->������;
    ��->������           = this->������;
    this->������         = ��->������;
    ��->������           = this;

    ��->������->���¸߶�();
    ��->������->���¸߶�();
    ��->���¸߶�();
}

template <typename DT>
void AVL��<DT>::������ת(AVL��<DT> *&��) {
    ��                   = this->������->������;
    this->������->������ = ��->������;
    ��->������           = this->������;
    this->������         = ��->������;
    ��->������           = this;

    ��->������->���¸߶�();
    ��->������->���¸߶�();
    ��->���¸߶�();
}

template <typename DT>
void AVL��<DT>::���¸߶�() {
    if (this) {
        int �������߶� = (������) ? ������->�߶� : 0;
        int �������߶� = (������) ? ������->�߶� : 0;
        this->�߶�     = 1 + ((�������߶� > �������߶�) ? �������߶� : �������߶�);
    }
}

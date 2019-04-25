//
// Created by Lyosha12 on 30.04.2018.
//

#ifndef LAB_3_CIRCLEITERATOR_HPP
#define LAB_3_CIRCLEITERATOR_HPP

template <class Iterator>
class CycleIterator {
    using CI = CycleIterator<Iterator>;
  public:
    CycleIterator(Iterator begin, Iterator end)
        : begin(begin)
        , end(end)
        , current(begin)
    { }
    
    decltype(*Iterator()) operator* () {
        return *current;
    }
    
    CI& operator++ () {
        ++current;
        if(current == end)
            current = begin;
        
        return *this;
    }
    CI& operator-- () {
        if(current == begin)
            current = end - 1;
        else
            --current;
        
        return *this;
    }
  
  private:
    Iterator begin, end, current;
};

#endif //LAB_3_CIRCLEITERATOR_HPP

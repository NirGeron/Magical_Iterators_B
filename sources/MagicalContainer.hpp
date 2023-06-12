#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP
#include <algorithm>
#include <vector>

namespace ariel {

    class MagicalContainer {
    private:
        std::vector<int> element_major;
        std::vector<int*> element_inc;
        std::vector<int*> element_cut;
        std::vector<int*> element_p;


    public:
        void addElement(int e);
        void removeElement(int e);
        int size() const;
        std::vector<int> getElements() const;
        MagicalContainer() = default; 
        ~MagicalContainer() = default; 
        void add_element_inc();
        void add_element_cut();
        void add_element_prime();

        MagicalContainer(MagicalContainer&& m) = default;
        MagicalContainer& operator=(MagicalContainer&& m) = default;
        MagicalContainer(const MagicalContainer& m) = default;
        MagicalContainer& operator=(const MagicalContainer& m) = default;

        class AscendingIterator {
        private:
            MagicalContainer& mc;
            std::vector<int*>::iterator iterator_inc;
            size_t location;

        public:
        
            AscendingIterator(AscendingIterator&& it) = default;
            AscendingIterator& operator=(AscendingIterator&& it) = delete;

            AscendingIterator& operator++();

            AscendingIterator(MagicalContainer& cont);
            AscendingIterator(const AscendingIterator& it);
            ~AscendingIterator() = default;

            bool operator>(const AscendingIterator& it) const;
            bool operator<(const AscendingIterator& it) const;
            bool operator==(const AscendingIterator& it) const;
            bool operator!=(const AscendingIterator& it) const;

            AscendingIterator& operator=(const AscendingIterator& it);

            int operator*() const;

            AscendingIterator &begin();
            AscendingIterator &end();
        };

        class SideCrossIterator {
        private:
            MagicalContainer& mc;
            std::vector<int*>::iterator iterator_cut;
            size_t location;

        public:
            SideCrossIterator(SideCrossIterator&& it) = default;
            SideCrossIterator& operator=(SideCrossIterator&& it) = delete;
            SideCrossIterator& operator++();
            SideCrossIterator(MagicalContainer& cont);
            SideCrossIterator(const SideCrossIterator& it);
            ~SideCrossIterator() = default;

            bool operator>(const SideCrossIterator& it) const;
            bool operator<(const SideCrossIterator& it) const;
            bool operator==(const SideCrossIterator& it) const;
            bool operator!=(const SideCrossIterator& it) const;

            SideCrossIterator& operator=(const SideCrossIterator& it);

            int operator*() const;

            SideCrossIterator &begin();
            SideCrossIterator &end();
        };

        class PrimeIterator {
        private:
            MagicalContainer& mc;
            std::vector<int*>::iterator iterator_p;
            size_t location;

        public:
        
            PrimeIterator &begin();
            PrimeIterator &end();
            PrimeIterator(PrimeIterator&& it) = default;
            PrimeIterator& operator=(PrimeIterator&& it) = delete;

            PrimeIterator& operator++();
            PrimeIterator(MagicalContainer& cont);
            PrimeIterator(const PrimeIterator& it);
            ~PrimeIterator() = default;

            bool operator>(const PrimeIterator& it) const;
            bool operator<(const PrimeIterator& it) const;
            bool operator==(const PrimeIterator& it) const;
            bool operator!=(const PrimeIterator& it) const;

            PrimeIterator& operator=(const PrimeIterator& it);
            
            int operator*() const;
        };

    };

} 


#endif
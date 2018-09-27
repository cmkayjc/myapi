#ifndef _MYAPI_ITERATOR_H__
#define _MYAPI_ITERATOR_H__

namespace MyAPI
{

template<typename T>
class Iterator
{
	public:
		Iterator(T* head, T* end):mp_head(head)
																,mp_end(end)
																,mp_cur(head)
		{}
		virtual ~Iterator() {}
		virtual const T operator* () const
		{
			return *mp_cur;
		};

		virtual T& operator* ()
		{
			return *mp_cur;
		};

		/// ++Item
		virtual Iterator& operator++() 
		{
			++mp_cur;
			return *this;
		};

		/**Item ++
		 * set return type to const 
		 * if you want to disable Item++++;
		 */
		virtual const Iterator& operator++(int) 
		{
			return ++(*this);
		};

		virtual bool operator!() const
		{
			return mp_cur == mp_end;
		};

		virtual bool operator!=(const Iterator<T>& in) const
		{
			return this->mp_cur != in.mp_cur;
		}

		virtual Iterator begin()
		{
			Iterator it(*this);
			it.mp_cur = it.mp_head;
			return it;
		}

		virtual Iterator end()
		{
			Iterator it(*this);
			it.mp_cur = it.mp_end;
			return it;
		}

	private:
		T* const mp_head;
		T* const mp_end;
		T* mp_cur;
}; //class Iterator

} // namespace MyAPI

#endif //_MY_MYITERATOR_H__

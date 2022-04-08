#include "Stream.h"

HRESULT __stdcall Stream::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == __uuidof(IStream          )
	||  riid == __uuidof(ISequentialStream)
	||  riid == __uuidof(IUnknown         )
	) {
		(reinterpret_cast<IStream*&>(*ppvObject) = this)->AddRef();
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}

ULONG __stdcall Stream::AddRef(void)
{
	return ++refcnt;
}

ULONG __stdcall Stream::Release(void)
{
	if (const auto new_count = --refcnt)
		return new_count;
	else {
		delete this;
		return 0UL;
	}
}

HRESULT __stdcall Stream::Read(void* pv, ULONG cb, ULONG* pcbRead)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::Write(const void* pv, ULONG cb, ULONG* pcbWritten)
{
	if (file.write(static_cast<const char*>(pv), cb)) {
		if (pcbWritten)
			*pcbWritten = cb;
		return S_OK;
	}
	else
		return E_FAIL;
}

HRESULT __stdcall Stream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::SetSize(ULARGE_INTEGER libNewSize)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::CopyTo(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::Commit(DWORD grfCommitFlags)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::Revert(void)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::Stat(STATSTG* pstatstg, DWORD grfStatFlag)
{
	return E_NOTIMPL;
}

HRESULT __stdcall Stream::Clone(IStream** ppstm)
{
	return E_NOTIMPL;
}

Stream::Stream(std::ofstream&& file) noexcept
	: refcnt{ 1UL }
	, file{ std::move(file) }
{
}

Stream* Stream::New(std::ofstream&& file)
{
	return new Stream(std::move(file));
}

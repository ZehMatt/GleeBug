#include "Debugger.Thread.Registers.h"

namespace GleeBug
{
    Registers::Registers(HANDLE hThread) :
        Dr0(this),
        Dr1(this),
        Dr2(this),
        Dr3(this),
        Dr6(this),
        Dr7(this),

        Eflags(this),

        Eax(this),
        Ax(this),
        Ah(this),
        Al(this),
        Ebx(this),
        Bx(this),
        Bh(this),
        Bl(this),
        Ecx(this),
        Cx(this),
        Ch(this),
        Cl(this),
        Edx(this),
        Dx(this),
        Dh(this),
        Dl(this),
        Edi(this),
        Di(this),
        Esi(this),
        Si(this),
        Ebp(this),
        Bp(this),
        Esp(this),
        Sp(this),
        Eip(this),

#ifdef _WIN64
        Rax(this),
        Rbx(this),
        Rcx(this),
        Rdx(this),
        Rsi(this),
        Sil(this),
        Rdi(this),
        Dil(this),
        Rbp(this),
        Bpl(this),
        Rsp(this),
        Spl(this),
        Rip(this),
        R8(this),
        R8d(this),
        R8w(this),
        R8b(this),
        R9(this),
        R9d(this),
        R9w(this),
        R9b(this),
        R10(this),
        R10d(this),
        R10w(this),
        R10b(this),
        R11(this),
        R11d(this),
        R11w(this),
        R11b(this),
        R12(this),
        R12d(this),
        R12w(this),
        R12b(this),
        R13(this),
        R13d(this),
        R13w(this),
        R13b(this),
        R14(this),
        R14d(this),
        R14w(this),
        R14b(this),
        R15(this),
        R15d(this),
        R15w(this),
        R15b(this),
#endif //_WIN64

        Gax(this),
        Gbx(this),
        Gcx(this),
        Gdx(this),
        Gdi(this),
        Gsi(this),
        Gbp(this),
        Gsp(this),
        Gip(this),

        Gs(this),
        Fs(this),
        Es(this),
        Ds(this),
        Cs(this),
        Ss(this),

        TrapFlag(this),
        ResumeFlag(this),
        mThread(hThread)
    {
        ReadContext();
    }

    Registers::~Registers()
    {
        WriteContext();
    }

    CONTEXT& Registers::GetContextForModify()
    {
        Invalidate();
        return mContext;
    }

    const CONTEXT& Registers::GetContext() const
    {
        return mContext;
    }

    void Registers::Invalidate()
    {
        mInvalidated = true;
    }

    bool Registers::ReadContext()
    {
        if(mThread == nullptr)
            return false;

        memset(&mContext, 0, sizeof(CONTEXT));
        mContext.ContextFlags = CONTEXT_ALL;
        if (!!GetThreadContext(mThread, &mContext))
        {
            memcpy(&mOldContext, &mContext, sizeof(CONTEXT));
            return true;
        }
        else
        {
            mThread = nullptr;
        }
        return false;
    }

    bool Registers::WriteContext()
    {
        if(mThread == nullptr)
            return false;

        if (mInvalidated && memcmp(&mContext, &mOldContext, sizeof(CONTEXT)) != 0)
        {
            mInvalidated = false;
            if (SetThreadContext(mThread, &mContext) == 0)
            {
                return false;
            }
        }
        return true;
    }

};
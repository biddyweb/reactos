#ifndef __NTOSKRNL_INCLUDE_INTERNAL_SAFE_H
#define __NTOSKRNL_INCLUDE_INTERNAL_SAFE_H

NTSTATUS MmSafeCopyFromUser(PVOID Dest, PVOID Src, ULONG NumberOfBytes);
NTSTATUS MmSafeCopyToUser(PVOID Dest, PVOID Src, ULONG NumberOfBytes);

NTSTATUS
MmCopyFromCaller(PVOID Dest, PVOID Src, ULONG NumberOfBytes);
NTSTATUS
MmCopyToCaller(PVOID Dest, PVOID Src, ULONG NumberOfBytes);

NTSTATUS
RtlCaptureUnicodeString(PUNICODE_STRING Dest,
			PUNICODE_STRING UnsafeSrc);

#endif /* __NTOSKRNL_INCLUDE_INTERNAL_SAFE_Hb */

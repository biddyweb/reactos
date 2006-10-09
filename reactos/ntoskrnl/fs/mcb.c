/* $Id$
 *
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/fs/mcb.c
 * PURPOSE:         No purpose listed.
 *
 * PROGRAMMERS:     No programmer listed.
 */

/* INCLUDES ****************************************************************/

#include <ntoskrnl.h>

#define NDEBUG
#include <internal/debug.h>

/* FUNCTIONS *****************************************************************/

/**********************************************************************
 * NAME							EXPORTED
 *
 * DESCRIPTION
 *
 * ARGUMENTS
 *
 * RETURN VALUE
 *
 * NOTES
 *
 * @unimplemented
 */
BOOLEAN
NTAPI
FsRtlAddLargeMcbEntry(IN PLARGE_MCB Mcb,
                      IN LONGLONG Vbn,
                      IN LONGLONG Lbn,
                      IN LONGLONG SectorCount)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*
 * FsRtlAddMcbEntry: Obsolete
 *
 * @implemented
 */
BOOLEAN
NTAPI
FsRtlAddMcbEntry(IN PMCB     Mcb,
                 IN VBN      Vbn,
                 IN LBN      Lbn,
                 IN ULONG    SectorCount)
{
    return FsRtlAddLargeMcbEntry(&Mcb->DummyFieldThatSizesThisStructureCorrectly,
                                 (LONGLONG)Vbn,
                                 (LONGLONG)Lbn,
                                 (LONGLONG)SectorCount);
}

/*
 * @unimplemented
 */
BOOLEAN
NTAPI
FsRtlGetNextLargeMcbEntry(IN PLARGE_MCB Mcb,
                          IN ULONG RunIndex,
                          OUT PLONGLONG Vbn,
                          OUT PLONGLONG Lbn,
                          OUT PLONGLONG SectorCount)
{
    UNIMPLEMENTED;
    return FALSE;
}


/*
 * @implemented
 */
BOOLEAN
NTAPI
FsRtlGetNextMcbEntry(IN PMCB     Mcb,
                     IN ULONG    RunIndex,
                     OUT PVBN    Vbn,
                     OUT PLBN    Lbn,
                     OUT PULONG  SectorCount)
{
    BOOLEAN Return = FALSE;
    LONGLONG llVbn;
    LONGLONG llLbn;
    LONGLONG llSectorCount;

    /* Call the Large version */
    Return = FsRtlGetNextLargeMcbEntry(&Mcb->DummyFieldThatSizesThisStructureCorrectly,
                                       RunIndex,
                                       &llVbn,
                                       &llLbn,
                                       &llSectorCount);

    /* Return everything typecasted */
    *Vbn = (ULONG)llVbn;
    *Lbn = (ULONG)llLbn;
    *SectorCount = (ULONG)llSectorCount;

    /* And return the original value */
    return(Return);
}


/*
 * @unimplemented
 */
VOID
NTAPI
FsRtlInitializeLargeMcb(IN PLARGE_MCB Mcb,
                        IN POOL_TYPE PoolType)
{
    UNIMPLEMENTED;
    Mcb->BaseMcb.PoolType = PoolType;
}

/*
 * FsRtlInitializeMcb: Obsolete
 * @implemented
 */
VOID
NTAPI
FsRtlInitializeMcb (IN PMCB         Mcb,
                    IN POOL_TYPE    PoolType)
{
    FsRtlInitializeLargeMcb(& Mcb->DummyFieldThatSizesThisStructureCorrectly, PoolType);
}

/*
 * @unimplemented
 */
BOOLEAN
NTAPI
FsRtlLookupLargeMcbEntry(IN PLARGE_MCB Mcb,
                         IN LONGLONG Vbn,
                         OUT PLONGLONG Lbn OPTIONAL,
                         OUT PLONGLONG SectorCountFromLbn OPTIONAL,
                         OUT PLONGLONG StartingLbn OPTIONAL,
                         OUT PLONGLONG SectorCountFromStartingLbn OPTIONAL,
                         OUT PULONG Index OPTIONAL)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*
 * @unimplemented
 */
BOOLEAN
NTAPI
FsRtlLookupLastLargeMcbEntryAndIndex(IN PLARGE_MCB OpaqueMcb,
                                     OUT PLONGLONG LargeVbn,
                                     OUT PLONGLONG LargeLbn,
                                     OUT PULONG Index)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*
 * @unimplemented
 */
PFSRTL_PER_STREAM_CONTEXT
NTAPI
FsRtlLookupPerStreamContextInternal(IN PFSRTL_ADVANCED_FCB_HEADER StreamContext,
                                    IN PVOID OwnerId OPTIONAL,
                                    IN PVOID InstanceId OPTIONAL)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*
 * @unimplemented
 */
PFSRTL_PER_FILEOBJECT_CONTEXT
NTAPI
FsRtlLookupPerFileObjectContext(IN PFILE_OBJECT FileObject,
                                IN PVOID OwnerId OPTIONAL,
                                IN PVOID InstanceId OPTIONAL)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*
 * @unimplemented
 */
BOOLEAN
NTAPI
FsRtlLookupLastLargeMcbEntry(IN PLARGE_MCB Mcb,
                             OUT PLONGLONG Vbn,
                             OUT PLONGLONG Lbn)
{
    UNIMPLEMENTED;
    return(FALSE);
}

/*
 * @implemented
 */
BOOLEAN
NTAPI
FsRtlLookupLastMcbEntry(IN PMCB Mcb,
                        OUT PVBN Vbn,
                        OUT PLBN Lbn)
{
    BOOLEAN Return = FALSE;
    LONGLONG llVbn;
    LONGLONG llLbn;

    /* Call the Large version */
    Return = FsRtlLookupLastLargeMcbEntry(&Mcb->DummyFieldThatSizesThisStructureCorrectly,
        &llVbn,
        &llLbn);

    /* Return everything typecasted */
    *Vbn = (ULONG)llVbn;
    *Lbn = (ULONG)llLbn;

    /* And return the original value */
    return(Return);
}

/*
 * @implemented
 */
BOOLEAN
NTAPI
FsRtlLookupMcbEntry(IN PMCB Mcb,
                    IN VBN Vbn,
                    OUT PLBN Lbn,
                    OUT PULONG SectorCount OPTIONAL,
                    OUT PULONG Index)
{
    BOOLEAN Return = FALSE;
    LONGLONG llLbn;
    LONGLONG llSectorCount;

    /* Call the Large version */
    Return = FsRtlLookupLargeMcbEntry(&Mcb->DummyFieldThatSizesThisStructureCorrectly,
                                      (LONGLONG)Vbn,
                                      &llLbn,
                                      &llSectorCount,
                                      NULL,
                                      NULL,
                                      Index);

    /* Return everything typecasted */
    *Lbn = (ULONG)llLbn;
    if (SectorCount) *SectorCount = (ULONG)llSectorCount;

    /* And return the original value */
    return(Return);
}

/*
 * @implemented
 */
ULONG
NTAPI
FsRtlNumberOfRunsInLargeMcb(IN PLARGE_MCB Mcb)
{
    ULONG NumberOfRuns;

    KeAcquireGuardedMutex(Mcb->GuardedMutex);
    NumberOfRuns = Mcb->BaseMcb.PairCount;
    KeReleaseGuardedMutex(Mcb->GuardedMutex);

    return NumberOfRuns;
}


/*
 * FsRtlNumberOfRunsInMcb: Obsolete
 *
 * @implemented
 */
ULONG
NTAPI
FsRtlNumberOfRunsInMcb (IN PMCB Mcb)
{
    return FsRtlNumberOfRunsInLargeMcb(&Mcb->DummyFieldThatSizesThisStructureCorrectly);
}


/*
 * @unimplemented
 */
VOID
NTAPI
FsRtlRemoveLargeMcbEntry(IN PLARGE_MCB Mcb,
                         IN LONGLONG Vbn,
                         IN LONGLONG SectorCount)
{
    UNIMPLEMENTED;
}

/*
 * @implemented
 */
VOID
NTAPI
FsRtlRemoveMcbEntry(IN PMCB     Mcb,
                    IN VBN      Vbn,
                    IN ULONG    SectorCount)
{
    /* Call the large function */
    FsRtlRemoveLargeMcbEntry(&Mcb->DummyFieldThatSizesThisStructureCorrectly,
                             (LONGLONG)Vbn,
                             (LONGLONG)SectorCount);
}


/*
 * @unimplemented
 */
VOID
NTAPI
FsRtlResetLargeMcb(IN PLARGE_MCB Mcb,
                   IN BOOLEAN SelfSynchronized)
{
    UNIMPLEMENTED;
}

/*
 * @unimplemented
 */
BOOLEAN
NTAPI
FsRtlSplitLargeMcb(IN PLARGE_MCB Mcb,
                   IN LONGLONG Vbn,
                   IN LONGLONG Amount)
{
    UNIMPLEMENTED;
    return FALSE;
}

/*
 * @unimplemented
 */
VOID
NTAPI
FsRtlTruncateLargeMcb(IN PLARGE_MCB Mcb,
                      IN LONGLONG Vbn)
{
    UNIMPLEMENTED;
}

/*
 * FsRtlTruncateMcb: Obsolete
 *
 * @implemented
 */
VOID
NTAPI
FsRtlTruncateMcb (IN PMCB Mcb,
                  IN VBN  Vbn)
{
    FsRtlTruncateLargeMcb(&Mcb->DummyFieldThatSizesThisStructureCorrectly, (LONGLONG)Vbn);
}

/*
 * @unimplemented
 */
VOID
NTAPI
FsRtlUninitializeLargeMcb(IN PLARGE_MCB Mcb)
{
    UNIMPLEMENTED;
}

/*
 * FsRtlUninitializeMcb: Obsolete
 *
 * @implemented
 */
VOID
NTAPI
FsRtlUninitializeMcb(IN PMCB Mcb)
{
    FsRtlUninitializeLargeMcb(& Mcb->DummyFieldThatSizesThisStructureCorrectly);
}

/* EOF */

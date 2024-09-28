
# Generated by OTF2 Template Engine

import _otf2


class _EnumWrapper(object):
    def __init__(self, prefix, enum_type=None):
        # This is a bit ugly, but IMHO at least less ugly than doing it in __getattr__
        self.__dict__['type'] = enum_type
        for (name, candidate) in _otf2.__dict__.items():
            if (enum_type is None or isinstance(candidate, enum_type)) and name.startswith(prefix):
                short_name = name[len(prefix):]
                self.__dict__[short_name] = candidate

    def __setattr__(self, name, value):
        raise AttributeError("Change of values is not allowed.")


# GeneralDefinitions
Undefined = _EnumWrapper("UNDEFINED_")

__all__ = ["Undefined", "FileMode", "FlushType", "Compression"]

FileMode = _otf2.FileMode
FlushType = _otf2.FlushType
Compression = _otf2.Compression

Boolean = _otf2.Boolean
__all__.append("Boolean")

FileType = _otf2.FileType
__all__.append("FileType")

FileSubstrate = _otf2.FileSubstrate
__all__.append("FileSubstrate")

MappingType = _otf2.MappingType
__all__.append("MappingType")

Type = _otf2.Type
__all__.append("Type")

Paradigm = _otf2.Paradigm
__all__.append("Paradigm")

ParadigmClass = _otf2.ParadigmClass
__all__.append("ParadigmClass")

ParadigmProperty = _otf2.ParadigmProperty
__all__.append("ParadigmProperty")

ThumbnailType = _otf2.ThumbnailType
__all__.append("ThumbnailType")

SystemTreeDomain = _otf2.SystemTreeDomain
__all__.append("SystemTreeDomain")

LocationGroupType = _otf2.LocationGroupType
__all__.append("LocationGroupType")

LocationType = _otf2.LocationType
__all__.append("LocationType")

RegionRole = _otf2.RegionRole
__all__.append("RegionRole")

RegionFlag = _otf2.RegionFlag
__all__.append("RegionFlag")

GroupType = _otf2.GroupType
__all__.append("GroupType")

GroupFlag = _otf2.GroupFlag
__all__.append("GroupFlag")

Base = _otf2.Base
__all__.append("Base")

MetricOccurrence = _otf2.MetricOccurrence
__all__.append("MetricOccurrence")

MetricType = _otf2.MetricType
__all__.append("MetricType")

MetricValueProperty = _otf2.MetricValueProperty
__all__.append("MetricValueProperty")

MetricTiming = _otf2.MetricTiming
__all__.append("MetricTiming")

MetricMode = _otf2.MetricMode
__all__.append("MetricMode")

MetricScope = _otf2.MetricScope
__all__.append("MetricScope")

RecorderKind = _otf2.RecorderKind
__all__.append("RecorderKind")

ParameterType = _otf2.ParameterType
__all__.append("ParameterType")

CartPeriodicity = _otf2.CartPeriodicity
__all__.append("CartPeriodicity")

InterruptGeneratorMode = _otf2.InterruptGeneratorMode
__all__.append("InterruptGeneratorMode")

MeasurementMode = _otf2.MeasurementMode
__all__.append("MeasurementMode")

CollectiveOp = _otf2.CollectiveOp
__all__.append("CollectiveOp")

RmaSyncType = _otf2.RmaSyncType
__all__.append("RmaSyncType")

RmaSyncLevel = _otf2.RmaSyncLevel
__all__.append("RmaSyncLevel")

LockType = _otf2.LockType
__all__.append("LockType")

RmaAtomicType = _otf2.RmaAtomicType
__all__.append("RmaAtomicType")

IoParadigmClass = _otf2.IoParadigmClass
__all__.append("IoParadigmClass")

IoParadigmFlag = _otf2.IoParadigmFlag
__all__.append("IoParadigmFlag")

IoParadigmProperty = _otf2.IoParadigmProperty
__all__.append("IoParadigmProperty")

IoHandleFlag = _otf2.IoHandleFlag
__all__.append("IoHandleFlag")

IoAccessMode = _otf2.IoAccessMode
__all__.append("IoAccessMode")

IoCreationFlag = _otf2.IoCreationFlag
__all__.append("IoCreationFlag")

IoStatusFlag = _otf2.IoStatusFlag
__all__.append("IoStatusFlag")

IoSeekOption = _otf2.IoSeekOption
__all__.append("IoSeekOption")

IoOperationMode = _otf2.IoOperationMode
__all__.append("IoOperationMode")

IoOperationFlag = _otf2.IoOperationFlag
__all__.append("IoOperationFlag")

CommFlag = _otf2.CommFlag
__all__.append("CommFlag")

RmaWinFlag = _otf2.RmaWinFlag
__all__.append("RmaWinFlag")

CollectiveRoot = _otf2.CollectiveRoot
__all__.append("CollectiveRoot")
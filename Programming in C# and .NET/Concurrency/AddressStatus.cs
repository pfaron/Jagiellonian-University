using System.Net.NetworkInformation;

namespace Concurrency
{
    public record AddressStatus(AddressEntry Entry, PingReply Status);
}
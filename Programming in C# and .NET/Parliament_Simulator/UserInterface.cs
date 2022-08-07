namespace Parliament_Simulator
{
    public static class UserInterface
    {
        public static void GetUserInput(Parliament parliament)
        {
            while (true)
            {
                Console.WriteLine("Type a command. Type HELP for help.");
                var command = "ERROR";
                var userInput = Console.ReadLine();
                if (userInput != null)
                    command = userInput.ToUpper().Trim();
                
                switch (command)
                {
                    case "ERROR":
                    {
                        Console.WriteLine("There has been an error getting user input.");
                        break;
                    }
                    case "EXIT":
                    {
                        return;
                    }
                    case "ADD":
                    {
                        Console.WriteLine("Write number of members you want to add:");

                        if (int.TryParse(Console.ReadLine(), out var number))
                            parliament.AddMembers(number);
                        else
                            Console.WriteLine("Input a number!");

                        break;
                    }
                    case "REMOVE":
                    {
                        Console.WriteLine("Write number of members you want to remove:");
                        
                        if(int.TryParse(Console.ReadLine(), out var number))
                            parliament.RemoveMembers(number);
                        else
                            Console.WriteLine("Input a number!");
                        
                        break;
                    }
                    case "VOTE":
                    {
                        Console.WriteLine("Write the number of the member of parliament you want to vote.");

                        if (int.TryParse(Console.ReadLine(), out var number))
                        {
                            if(number <= 0 || number > parliament.GetNumberOfMembers())
                                Console.WriteLine("There is no member with that number. There are currently "
                                + parliament.GetNumberOfMembers() + " members in parliament.");
                            else
                                parliament.GetMemberByNumber(number - 1).Vote();
                        }
                        else
                            Console.WriteLine("Input a number!");
                        
                        break;
                    }
                    case "START":
                    {
                        Console.WriteLine("Type the topic of voting:");
                        
                        var topic = Console.ReadLine();
                        if(topic != null)
                            parliament.StartVoting(topic);
                        else
                            Console.WriteLine("Error getting user input. No voting started.");
                        
                        break;
                    }
                    case "END":
                    {
                        parliament.EndVoting();
                        
                        break;
                    }
                    case "CURR":
                    {
                        var curr = parliament.GetCurrentVotingData();

                        if (curr == VotingData.GetNoVotingData())
                        {
                            Console.WriteLine("No voting currently!");
                            break;
                        }
                        
                        Console.WriteLine("Current voting's topic is: " + curr.VotingTopic);
                        Console.WriteLine("Total votes: " + curr.NumberOfVotes);
                        Console.WriteLine("For: " + curr.NumberOfPositiveVotes + " Against: "
                                          + (curr.NumberOfVotes - curr.NumberOfPositiveVotes));
                        break;
                    }
                    case "LAST":
                    {
                        var last = parliament.GetLastVotingData();
                        
                        if (last == VotingData.GetNoVotingData())
                        {
                            Console.WriteLine("No voting has taken place yet!");
                            break;
                        }
                        Console.WriteLine("Last voting's topic was: " + last.VotingTopic);
                        Console.WriteLine("Total votes: " + last.NumberOfVotes);
                        Console.WriteLine("For: " + last.NumberOfPositiveVotes + " Against: "
                                          + (last.NumberOfVotes - last.NumberOfPositiveVotes));
                        break;
                    }
                    case "HELP":
                    {
                        DisplayHelp();
                        break;
                    }
                    case "COUNT":
                    {
                        Console.WriteLine("There are currently " + parliament.GetNumberOfMembers() + " members in parliament.");
                        break;
                    }
                    default:
                    {
                        Console.WriteLine("Incorrect command!");
                        break;
                    }
                }
            }
        }

        private static void DisplayHelp()
        {
            Console.WriteLine("EXIT - exits the application;\nADD - adds members to the parliament;");
            Console.WriteLine("REMOVE - removes members from the parliament;\nVOTE - makes chosen parliament member vote;");
            Console.WriteLine("START - sets a topic and starts a voting;\nEND - ends a voting;");
            Console.WriteLine("CURR - displays results of current voting;");
            Console.WriteLine("LAST - displays results of the last voting;\nCOUNT - returns the current number of members.");
        }
    }
}
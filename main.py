import requests
from bs4 import BeautifulSoup
import re
from urllib.parse import urljoin

def search_github_repo(repo_url, search_word):
    # Send an HTTP GET request to the GitHub repository page
    response = requests.get(repo_url)
    if response.status_code == 200:
        # Parse the HTML content of the page
        soup = BeautifulSoup(response.content, 'html.parser')
        # Extract links to all the folders in the repository
        folder_links = [link['href'] for link in soup.find_all('a', href=True) if link['href'].endswith('/')]
        for folder_link in folder_links:
            folder_url = urljoin(repo_url, folder_link)
            # Check if the folder URL belongs to the same repository
            if folder_url.startswith(repo_url):
                folder_response = requests.get(folder_url)
                if folder_response.status_code == 200:
                    folder_soup = BeautifulSoup(folder_response.content, 'html.parser')
                    # Search the content of the folder page for the search word
                    if re.search(search_word, folder_soup.get_text()):
                        print(f"Found '{search_word}' in folder: {folder_url}")
                else:
                    print(f"Failed to retrieve folder content: {folder_url}")
    else:
        print("Failed to retrieve repository page")

# Example usage:
repo_url = 'https://github.com/open-watcom/open-watcom-v2'
search_word = 'example'  # Change 'example' to the word you want to search for
search_github_repo(repo_url, search_word)
